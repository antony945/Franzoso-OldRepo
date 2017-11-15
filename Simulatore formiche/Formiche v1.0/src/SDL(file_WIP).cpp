#include "SDLclass.h"



typedef struct tColorRGBA {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} tColorRGBA;

int _shrinkSurfaceRGBA(SDL_Surface * src, SDL_Surface* dst, int factorx, int factory)
{

	int x, y, dx, dy, dgap, ra, ga, ba, aa;
	int n_average;
	tColorRGBA *sp, *osp, *oosp;
	tColorRGBA *dp;

	/*
	* Averaging integer shrink
	*/

	/* Precalculate division factor */
	n_average = factorx*factory;

	/*
	* Scan destination
	*/
	sp = (tColorRGBA *)src->pixels;

	dp = (tColorRGBA *)dst->pixels;
	dgap = dst->pitch - dst->w * 4;

	for (y = 0; y < dst->h; y++) {

		osp = sp;
		for (x = 0; x < dst->w; x++) {

			/* Trace out source box and accumulate */
			oosp = sp;
			ra = ga = ba = aa = 0;
			for (dy = 0; dy < factory; dy++) {
				for (dx = 0; dx < factorx; dx++) {
					ra += sp->r;
					ga += sp->g;
					ba += sp->b;
					aa += sp->a;

					sp++;
				}
				/* src dx loop */
				sp = (tColorRGBA *)((Uint8*)sp + (src->pitch - 4 * factorx)); // next y
			}
			/* src dy loop */

			/* next box-x */
			sp = (tColorRGBA *)((Uint8*)oosp + 4 * factorx);

			/* Store result in destination */
			dp->r = ra / n_average;
			dp->g = ga / n_average;
			dp->b = ba / n_average;
			dp->a = aa / n_average;

			/*
			* Advance destination pointer
			*/
			dp++;
		}
		/* dst x loop */

		/* next box-y */
		sp = (tColorRGBA *)((Uint8*)osp + src->pitch*factory);

		/*
		* Advance destination pointers
		*/
		dp = (tColorRGBA *)((Uint8 *)dp + dgap);
	}
	/* dst y loop */

	return 0;
}

int _shrinkSurfaceY(SDL_Surface * src, SDL_Surface * dst, int factorx, int factory)
{
	int x, y, dx, dy, dgap, a;
	int n_average;
	Uint8 *sp, *osp, *oosp;
	Uint8 *dp;

	/*
	* Averaging integer shrink
	*/

	/* Precalculate division factor */
	n_average = factorx*factory;

	/*
	* Scan destination
	*/
	sp = (Uint8 *)src->pixels;

	dp = (Uint8 *)dst->pixels;
	dgap = dst->pitch - dst->w;

	for (y = 0; y < dst->h; y++) {

		osp = sp;
		for (x = 0; x < dst->w; x++) {

			/* Trace out source box and accumulate */
			oosp = sp;
			a = 0;
			for (dy = 0; dy < factory; dy++) {
				for (dx = 0; dx < factorx; dx++) {
					a += (*sp);
					/* next x */
					sp++;
				}
				/* end src dx loop */
				/* next y */
				sp = (Uint8 *)((Uint8*)sp + (src->pitch - factorx));
			}
			/* end src dy loop */

			/* next box-x */
			sp = (Uint8 *)((Uint8*)oosp + factorx);

			/* Store result in destination */
			*dp = a / n_average;

			/*
			* Advance destination pointer
			*/
			dp++;
		}
		/* end dst x loop */

		/* next box-y */
		sp = (Uint8 *)((Uint8*)osp + src->pitch*factory);

		/*
		* Advance destination pointers
		*/
		dp = (Uint8 *)((Uint8 *)dp + dgap);
	}
	/* end dst y loop */

	return (0);
}

void Sprite::shrinkSurface(int index, int factorx, int factory)
{

	int result;
	SDL_Surface *rz_src;
	SDL_Surface *rz_dst = NULL;
	int dstwidth, dstheight;
	int is32bit;
	int i, src_converted;
	int haveError = 0;
	SDL_Surface* src = s.at(index);
	/*
	* Sanity check
	*/
	if (src == NULL) {
		s.at(index)=NULL;
	}

	/*
	* Determine if source surface is 32bit or 8bit
	*/
	is32bit = (src->format->BitsPerPixel == 32);
	if ((is32bit) || (src->format->BitsPerPixel == 8)) {
		/*
		* Use source surface 'as is'
		*/
		rz_src = src;
		src_converted = 0;
	}
	else {
		/*
		* New source surface is 32bit with a defined RGBA ordering
		*/
		rz_src = SDL_CreateRGBSurface(SDL_SWSURFACE, src->w, src->h, 32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
			0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
#else
			0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff
#endif
		);
		if (rz_src == NULL) {
			haveError = 1;
			goto exitShrinkSurface;
		}

		SDL_BlitSurface(src, NULL, rz_src, NULL);
		src_converted = 1;
		is32bit = 1;
	}

	/*
	* Lock the surface
	*/
	if (SDL_MUSTLOCK(rz_src)) {
		if (SDL_LockSurface(rz_src) < 0) {
			haveError = 1;
			goto exitShrinkSurface;
		}
	}

	/* Get size for target */
	dstwidth = rz_src->w / factorx;
	while (dstwidth*factorx>rz_src->w) { dstwidth--; }
	dstheight = rz_src->h / factory;
	while (dstheight*factory>rz_src->h) { dstheight--; }

	/*
	* Alloc space to completely contain the shrunken surface
	* (with added guard rows)
	*/
	if (is32bit == 1) {
		/*
		* Target surface is 32bit with source RGBA/ABGR ordering
		*/
		rz_dst =
			SDL_CreateRGBSurface(SDL_SWSURFACE, dstwidth, dstheight + GUARD_ROWS, 32,
				rz_src->format->Rmask, rz_src->format->Gmask,
				rz_src->format->Bmask, rz_src->format->Amask);
	}
	else {
		/*
		* Target surface is 8bit
		*/
		rz_dst = SDL_CreateRGBSurface(SDL_SWSURFACE, dstwidth, dstheight + GUARD_ROWS, 8, 0, 0, 0, 0);
	}

	/* Check target */
	if (rz_dst == NULL) {
		haveError = 1;
		goto exitShrinkSurface;
	}

	/* Adjust for guard rows */
	rz_dst->h = dstheight;

	/*
	* Check which kind of surface we have
	*/
	if (is32bit == 1) {
		/*
		* Call the 32bit transformation routine to do the shrinking (using alpha)
		*/
		result = _shrinkSurfaceRGBA(rz_src, rz_dst, factorx, factory);
		if ((result != 0) || (rz_dst == NULL)) {
			haveError = 1;
			goto exitShrinkSurface;
		}
	}
	else {
		/*
		* Copy palette and colorkey info
		*/
		for (i = 0; i < rz_src->format->palette->ncolors; i++) {
			rz_dst->format->palette->colors[i] = rz_src->format->palette->colors[i];
		}
		rz_dst->format->palette->ncolors = rz_src->format->palette->ncolors;
		/*
		* Call the 8bit transformation routine to do the shrinking
		*/
		result = _shrinkSurfaceY(rz_src, rz_dst, factorx, factory);
		if (result != 0) {
			haveError = 1;
			goto exitShrinkSurface;
		}
	}

exitShrinkSurface:
	if (rz_src != NULL) {
		/*
		* Unlock source surface
		*/
		if (SDL_MUSTLOCK(rz_src)) {
			SDL_UnlockSurface(rz_src);
		}

		/*
		* Cleanup temp surface
		*/
		if (src_converted == 1) {
			SDL_FreeSurface(rz_src);
		}
	}

	/* Check error state; maybe need to cleanup destination */
	if (haveError == 1) {
		if (rz_dst != NULL) {
			SDL_FreeSurface(rz_dst);
		}
		rz_dst = NULL;
	}

	/*
	* Return destination surface
	*/
	

	s.at(index)=rz_dst;
	SDL_SetColorKey(s.at(index), SDL_TRUE, SDL_MapRGB(s.at(index)->format, 0xFF, 0xFF, 0xFF));
}

int _HLineTextured(SDL_Renderer *renderer, Sint16 x1, Sint16 x2, Sint16 y, SDL_Texture *texture, int texture_w, int texture_h, int texture_dx, int texture_dy, int x_start, int y_start)
{
	Sint16 w;
	Sint16 xtmp;
	int result = 0;
	int texture_x_walker;
	int texture_y_start;
	SDL_Rect source_rect, dst_rect;
	int pixels_written, write_width;

	/*
	* Swap x1, x2 if required to ensure x1<=x2
	*/
	if (x1 > x2) {
		xtmp = x1;
		x1 = x2;
		x2 = xtmp;
	}

	/*
	* Calculate width to draw
	*/
	w = x2 - x1 + 1;

	/*
	* Determine where in the texture we start drawing
	*/
	texture_x_walker = (x1 - x_start - texture_dx) % texture_w;
	if (texture_x_walker < 0) {
		texture_x_walker = texture_w + texture_x_walker;
	}

	texture_y_start = (y - y_start + texture_dy) % texture_h;
	if (texture_y_start < 0) {
		texture_y_start = texture_h + texture_y_start;
	}

	/* setup the source rectangle; we are only drawing one horizontal line */
	source_rect.y = texture_y_start;
	source_rect.x = texture_x_walker;
	source_rect.h = 1;






	/* we will draw to the current y */
	dst_rect.y = y;
	dst_rect.h = 1;

	/* if there are enough pixels left in the current row of the texture */
	/* draw it all at once */
	if (w <= texture_w - texture_x_walker) {
		source_rect.w = w;
		source_rect.x = texture_x_walker;




		dst_rect.x = x1;
		dst_rect.w = source_rect.w;
		result = (SDL_RenderCopy(renderer, texture, &source_rect, &dst_rect) == 0);
	}
	else {
		/* we need to draw multiple times */
		/* draw the first segment */
		pixels_written = texture_w - texture_x_walker;
		source_rect.w = pixels_written;
		source_rect.x = texture_x_walker;


		dst_rect.x = x1;
		dst_rect.w = source_rect.w;
		result |= (SDL_RenderCopy(renderer, texture, &source_rect, &dst_rect) == 0);
		write_width = texture_w;

		/* now draw the rest */
		/* set the source x to 0 */
		source_rect.x = 0;
		while (pixels_written < w) {
			if (write_width >= w - pixels_written) {
				write_width = w - pixels_written;
			}
			source_rect.w = write_width;
			dst_rect.x = x1 + pixels_written;
			dst_rect.w = source_rect.w;
			result |= (SDL_RenderCopy(renderer, texture, &source_rect, &dst_rect) == 0);
			pixels_written += write_width;
		}
	}

	return result;
}

int CompareInt(const void *a, const void *b)
{
	return (*(const int *)a) - (*(const int *)b);
}

int hline(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y)
{
	return SDL_RenderDrawLine(renderer, x1, y, x2, y);;
}

int polygon(SDL_Renderer * renderer, std::vector<int> vx, std::vector<int> vy, int n)
{
	/*
	* Draw
	*/
	int result = 0;
	int i, nn;
	SDL_Point* points;

	/*
	* Vertex array NULL check
	*/

	/*
	* Sanity check
	*/
	if (n < 3) {
		return (-1);
	}

	/*
	* Create array of points
	*/
	nn = n + 1;
	points = (SDL_Point*)malloc(sizeof(SDL_Point) * nn);
	if (points == NULL)
	{
		return -1;
	}
	for (i = 0; i<n; i++)
	{
		points[i].x = vx[i];
		points[i].y = vy[i];
	}
	points[n].x = vx[0];
	points[n].y = vy[0];

	/*
	* Draw
	*/
	result |= SDL_RenderDrawLines(renderer, points, nn);
	free(points);

	return (result);
}

int polygonRGBA(SDL_Renderer * renderer, std::vector<int> vx, std::vector<int> vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw
	*/
	int result;
	const Sint16 *x1, *y1, *x2, *y2;

	/*
	* Vertex array NULL check
	*/

	/*
	* Sanity check
	*/
	if (n < 3) {
		return (-1);
	}

	/*
	* Pointer setup
	x1 = x2 = vx;
	y1 = y2 = vy;
	x2++;
	y2++;
	*/
	/*
	* Set color
	*/
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	/*
	* Draw
	*/
	result |= polygon(renderer, vx, vy, n);

	return (result);
}

int filledPolygonRGBAMT(SDL_Renderer * renderer, std::vector<long double> vx, std::vector<long double> vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int **polyInts, int *polyAllocated, int heightmax)
{
	int result;
	int i;
	int y, xa, xb;
	int miny, maxy;
	int x1, y1;
	int x2, y2;
	int ind1, ind2;
	int ints;
	int *PolyInts = NULL;
	int *PolyIntsNew = NULL;
	int PolyAllocated = 0;

	/*
	* Vertex array NULL check
	*/


	/*
	* Sanity check number of edges
	*/
	if (n < 3) {
		return -1;
	}

	/*
	* Map polygon cache
	*/
	if ((polyInts == NULL) || (polyAllocated == NULL)) {
		/* Use global cache */
		PolyInts = PolyIntsGlobal;
		PolyAllocated = PolyAllocatedGlobal;
	}
	else {
		/* Use local cache */
		PolyInts = *polyInts;
		PolyAllocated = *polyAllocated;
	}

	/*
	* Allocate temp array, only grow array
	*/
	if (!PolyAllocated) {
		PolyInts = (int *)malloc(sizeof(int) * n);
		PolyAllocated = n;
	}
	else {
		if (PolyAllocated < n) {
			PolyIntsNew = (int *)realloc(PolyInts, sizeof(int) * n);
			if (!PolyIntsNew) {
				if (!PolyInts) {
					free(PolyInts);
					PolyInts = NULL;
				}
				PolyAllocated = 0;
			}
			else {
				PolyInts = PolyIntsNew;
				PolyAllocated = n;
			}
		}
	}

	/*
	* Check temp array
	*/
	if (PolyInts == NULL) {
		PolyAllocated = 0;
	}

	/*
	* Update cache variables
	*/
	if ((polyInts == NULL) || (polyAllocated == NULL)) {
		PolyIntsGlobal = PolyInts;
		PolyAllocatedGlobal = PolyAllocated;
	}
	else {
		*polyInts = PolyInts;
		*polyAllocated = PolyAllocated;
	}

	/*
	* Check temp array again
	*/
	if (PolyInts == NULL) {
		return(-1);
	}

	/*
	* Determine Y maxima
	*/
	miny = vy[0];
	maxy = vy[0];
	for (i = 1; (i < n); i++) {
		if (vy[i] < miny) {
			miny = vy[i];
		}
		else if (vy[i] > maxy) {
			maxy = vy[i];
		}
	}
	if (maxy > heightmax) {
		maxy = heightmax;
	}
	/*
	* Draw, scanning y
	*/
	result = 0;
	for (y = miny; (y <= maxy); y++) {
		//	std::cout << maxy << " " << y<< "\n";
		ints = 0;
		for (i = 0; (i < n); i++) {
			if (!i) {
				ind1 = n - 1;
				ind2 = 0;
			}
			else {
				ind1 = i - 1;
				ind2 = i;
			}
			y1 = vy[ind1];
			y2 = vy[ind2];
			if (y1 < y2) {
				x1 = vx[ind1];
				x2 = vx[ind2];
			}
			else if (y1 > y2) {
				y2 = vy[ind1];
				y1 = vy[ind2];
				x2 = vx[ind1];
				x1 = vx[ind2];
			}
			else {
				continue;
			}
			if (((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2))) {
				PolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
			}
		}

		qsort(PolyInts, ints, sizeof(int), CompareInt);

		/*
		* Set color
		*/
		result = 0;
		result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
		result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

		for (i = 0; (i < ints); i += 2) {

			xa = PolyInts[i] + 1;
			xa = (xa >> 16) + ((xa & 32768) >> 15);
			xb = PolyInts[i + 1] - 1;
			xb = (xb >> 16) + ((xb & 32768) >> 15);
			result |= hline(renderer, xa, xb, y);
		}
	}

	return (result);
}

int filledPolygonRGBA(SDL_Renderer * renderer, std::vector<long double> vx, std::vector<long double> vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int heightmax)
{
	return filledPolygonRGBAMT(renderer, vx, vy, n, r, g, b, a, NULL, NULL, heightmax);
}

int texturedPolygonMT(SDL_Renderer *renderer, std::vector<long double> vx, std::vector<long double> vy, int n,
	SDL_Surface * texture, int texture_dx, int texture_dy, int **polyInts, int *polyAllocated, int x_start, int y_start)
{
	int result;
	int i;
	int y, xa, xb;
	int minx, maxx, miny, maxy;
	int x1, y1;
	int x2, y2;
	int ind1, ind2;
	int ints;
	int *PolyInts = NULL;
	int *PolyIntsTemp = NULL;
	int PolyAllocated = 0;
	SDL_Texture *textureAsTexture = NULL;

	/*
	* Sanity check number of edges
	*/
	if (n < 3) {
		return -1;
	}

	/*
	* Map polygon cache
	*/
	if ((polyInts == NULL) || (polyAllocated == NULL)) {
		/* Use global cache */
		PolyInts = PolyIntsGlobal;
		PolyAllocated = PolyAllocatedGlobal;
	}
	else {
		/* Use local cache */
		PolyInts = *polyInts;
		PolyAllocated = *polyAllocated;
	}

	/*
	* Allocate temp array, only grow array
	*/
	if (!PolyAllocated) {
		PolyInts = (int *)malloc(sizeof(int) * n);
		PolyAllocated = n;
	}
	else {
		if (PolyAllocated < n) {
			PolyIntsTemp = (int *)realloc(PolyInts, sizeof(int) * n);
			if (PolyIntsTemp == NULL) {
				/* Realloc failed - keeps original memory block, but fails this operation */
				return(-1);
			}
			PolyInts = PolyIntsTemp;
			PolyAllocated = n;
		}
	}

	/*
	* Check temp array
	*/
	if (PolyInts == NULL) {
		PolyAllocated = 0;
	}

	/*
	* Update cache variables
	*/
	if ((polyInts == NULL) || (polyAllocated == NULL)) {
		PolyIntsGlobal = PolyInts;
		PolyAllocatedGlobal = PolyAllocated;
	}
	else {
		*polyInts = PolyInts;
		*polyAllocated = PolyAllocated;
	}

	/*
	* Check temp array again
	*/
	if (PolyInts == NULL) {
		return(-1);
	}

	/*
	* Determine X,Y minima,maxima
	*/
	miny = vy[0];
	maxy = vy[0];
	minx = vx[0];
	maxx = vx[0];
	for (i = 1; (i < n); i++) {
		if (vy[i] < miny) {
			miny = vy[i];
		}
		else if (vy[i] > maxy) {
			maxy = vy[i];
		}
		if (vx[i] < minx) {
			minx = vx[i];
		}
		else if (vx[i] > maxx) {
			maxx = vx[i];
		}
	}

	/* Create texture for drawing */
	textureAsTexture = SDL_CreateTextureFromSurface(renderer, texture);
	if (textureAsTexture == NULL)
	{
		return -1;
	}
	SDL_SetTextureBlendMode(textureAsTexture, SDL_BLENDMODE_BLEND);

	/*
	* Draw, scanning y
	*/
	result = 0;
	for (y = miny; (y <= maxy); y++) {
		ints = 0;
		for (i = 0; (i < n); i++) {
			if (!i) {
				ind1 = n - 1;
				ind2 = 0;
			}
			else {
				ind1 = i - 1;
				ind2 = i;
			}
			y1 = vy[ind1];
			y2 = vy[ind2];
			if (y1 < y2) {
				x1 = vx[ind1];
				x2 = vx[ind2];
			}
			else if (y1 > y2) {
				y2 = vy[ind1];
				y1 = vy[ind2];
				x2 = vx[ind1];
				x1 = vx[ind2];
			}
			else {
				continue;
			}
			if (((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2))) {
				PolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
			}
		}

		qsort(PolyInts, ints, sizeof(int), CompareInt);

		for (i = 0; (i < ints); i += 2) {
			xa = PolyInts[i] + 1;
			xa = (xa >> 16) + ((xa & 32768) >> 15);
			xb = PolyInts[i + 1] - 1;
			xb = (xb >> 16) + ((xb & 32768) >> 15);
			result |= _HLineTextured(renderer, xa, xb, y, textureAsTexture, texture->w, texture->h, texture_dx, texture_dy, x_start, y_start);
		}
	}


	SDL_DestroyTexture(textureAsTexture);

	return (result);
}

int texturedPolygon(SDL_Renderer *renderer, std::vector<long double> vx, std::vector<long double> vy, int n, SDL_Surface *texture, int texture_dx, int texture_dy, int x_start, int y_start)
{
	/*
	* Draw
	*/
	return (texturedPolygonMT(renderer, vx, vy, n, texture, texture_dx, texture_dy, NULL, NULL, x_start, y_start));
}

int pnpoly(int nvert, vector<int> vertx, vector<int> verty, float testx, float testy)
{
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((verty[i]>testy) != (verty[j]>testy)) &&
			(testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
			c = !c;
	}
	return c;
}

Vettore& Vettore::operator+=(const Vettore& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vettore& Vettore::operator-=(const Vettore& v) {
	return *this += -v;
}

Vettore& Vettore::operator*=(long double scalar) {
	x = x*scalar;
	y = y*scalar;
	return *this;
}

Vettore& Vettore::operator/=(long double scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}

Vettore operator-(const Vettore& v) {
	return Vettore{ -v.x, -v.y };
}

Vettore operator+(const Vettore& a, const Vettore& b) {
	Vettore sum= a ;
	sum += b;
	return sum;
}

Vettore operator-(const Vettore& a, const Vettore& b) {
	Vettore difference=a ;
	difference -= b;
	return difference;
}

Vettore operator*(const Vettore& a, long double scalar) {
	Vettore product = a ;
	product *= scalar;
	return product;
}

Vettore operator/(const Vettore& a, long double scalar) {
	Vettore quotient= a ;
	quotient /= scalar;
	return quotient;
}

bool operator==(const Vettore& a, const Vettore& b) {
	return a.x == b.x && a.y == b.y;
}

bool operator!=(const Vettore& a, const Vettore& b) {
	return !(a == b);
}

Vettore Sprite::resultant() {
	Vettore resultant{};
	for (auto i : forces) {
		resultant += i.second;
	}
	return resultant;

}

void Sprite::update_velocity(std::chrono::duration<long double> delta_t) {
	velocity += resultant();
	velocity *= delta_t.count();
	velocity /= mass;


}

void Sprite::update_pos(chrono::duration<long double> delta_t, const Vettore& old_v)
{
	Vettore position{ x, y };
	Vettore average_vel = (velocity + old_v) / 2;
	position += average_vel * delta_t.count();
	old_x = x;
	old_y = y;
	x = position.x;
	y = position.y;

}

pair<map<string, Vettore>::iterator, bool> Sprite::apply_force(Vettore v, string key) {
	update_position();
	return forces.insert(pair<string, Vettore>(key, v));
}

map<string, Vettore>::size_type Sprite::remove_force(string key) {
	update_position();
	return forces.erase(key);
}

void Sprite::update_position() {
	auto delta_t = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - last_update);
	Vettore old_v(velocity);
	update_velocity(delta_t);
	update_pos(delta_t, old_v);
	update_collision_polygon();
	last_update = chrono::steady_clock::now();
}

Sprite::Sprite(const string& sprite_texture_path, long double x, long double y, int w, int h, int layer, SDL_Renderer* renderer)
	: x{ x }, y{ y }, width{ w }, height{ h }, layer{ layer }, last_update{ chrono::steady_clock::now() }
{
	s = CreateSurfaces(sprite_texture_path, renderer);
	collision_polygonx.push_back(x);
	collision_polygonx.push_back(x + w);
	collision_polygonx.push_back(x + w);
	collision_polygonx.push_back(x);
	collision_polygony.push_back(y);
	collision_polygony.push_back(y);
	collision_polygony.push_back(y + h);
	collision_polygony.push_back(y + h);
}

SDL_Surface* Sprite::load_texture(string path, SDL_Renderer* renderer) {
	//Load image at specified path
	if (paths.find(path) == paths.end()) {
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface != NULL) { SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF)); }
		paths.insert(pair<string, SDL_Surface*>(path, loadedSurface));
		return loadedSurface;
	}
	else
	{
		return paths.at(path);
	}
}

vector<SDL_Surface*> Sprite::CreateSurfaces(const string& folder_path, SDL_Renderer* renderer) {
	vector<SDL_Surface*> s;
	experimental::filesystem::directory_iterator d{ experimental::filesystem::path{ folder_path } };
	for (auto i : d) {
		string path{ i.path().string() };
		SDL_Surface* surface{ NULL };

		if ((surface = load_texture(path, renderer)) != NULL) {
			s.push_back(surface);
		}
	}
	return s;
}

void Sprite::change_texture(const string& new_texture_path, SDL_Renderer* renderer) {
	load_texture(new_texture_path, renderer);
}

void Sprite::change_collision_polygon(std::vector<SDL_Point> points) {
	collision_polygonx.clear();
	collision_polygony.clear();
	for (int i = 0; i < points.size(); i++) {
		collision_polygonx.push_back(x + points.at(i).x);
		collision_polygony.push_back(y + points.at(i).y);
	}
}

void Sprite::update_collision_polygon() {

	for (int i = 0; i < collision_polygonx.size(); i++) {
		collision_polygonx[i] += x - old_x;

	}
	for (int i = 0; i < collision_polygony.size(); i++) {
		collision_polygony[i] += y - old_y;

	}
}

void Sprite::teleport(int new_x, int new_y) {
	old_x = x;
	old_y = y;
	x = (long double)new_x;
	y = (long double)new_y;
	update_collision_polygon();
}

void Sprite::insert_collision_vertex(int vertex_index, SDL_Point new_pos) {
	std::vector<long double>::iterator it = collision_polygonx.begin();
	std::vector<long double>::iterator it2 = collision_polygony.begin();
	it += vertex_index;
	it2 += vertex_index;
	collision_polygonx.insert(it, new_pos.x);
	collision_polygony.insert(it2, new_pos.y);
}
void Sprite::insert_collision_vertex_array(int vertex_index, vector<SDL_Point> new_pos) {
	std::vector<long double>::iterator it = collision_polygonx.begin();
	std::vector<long double>::iterator it2 = collision_polygony.begin();
	it += vertex_index;
	it2 += vertex_index;
	std::vector<int> x;
	std::vector<int> y;
	for (int i = 0; i < new_pos.size(); i++) {
		x.push_back(new_pos[i].x);
		y.push_back(new_pos[i].y);
	}
	collision_polygonx.insert(it, x.begin(), x.end());
	collision_polygony.insert(it2, y.begin(), y.end());
	x.clear();
	y.clear();
	new_pos.clear();
}
void Sprite::move_collision_vertex(int vertex_index, SDL_Point new_pos) {
	collision_polygonx.at(vertex_index) = new_pos.x;
	collision_polygony.at(vertex_index) = new_pos.y;
}
void Sprite::remove_collision_vertex(int vertex_index, int number_of_vertices) {
	std::vector<long double>::iterator it = collision_polygonx.begin();
	std::vector<long double>::iterator it2 = collision_polygony.begin();
	it += vertex_index;
	it2 += vertex_index;
	collision_polygonx.erase(it, it + number_of_vertices);
	collision_polygony.erase(it2, it2 + number_of_vertices);
}

SDLclass::SDLclass(const char* title, int x, int y, int w, int h, string data_file)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw runtime_error(string("Failed to initialze SDL: ") + SDL_GetError());
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		throw runtime_error(string("Failed to initialze SDL_Image: ") + IMG_GetError());
	}
	window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		throw runtime_error(string("Failed to create window: ") + SDL_GetError());
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		throw runtime_error(string("Failed to create renderer: ") + SDL_GetError());
	}
	add_sprite_ptr<Sprite>("black_pixel", 0, black_pixel_path, -1, -1, -1, 1);
	WIDTH = w;
	HEIGHT = h;
	LoadSprites(data_file);

}

SDLclass::~SDLclass()
{
	layers.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	paths.clear();
}

void SDLclass::remove_sprite(const string& sprite_name, int layer)
{
	delete layers.at(layer).sprite.at(sprite_name).get();
	layers.at(layer).sprite.erase(sprite_name);
}

void SDLclass::reload_screen()
{
	SDL_RenderClear(renderer);
	int lay = 0;
	for (auto& i : layers) {
		if (i.sprite.size() != 0) {
			for (auto& s : i.sprite) {
				if (s.first != "light_corners" && s.first != "black_pixel") {



					if (s.second.get()->surface_index == s.second.get()->s.size()) {
						s.second.get()->surface_index = 0;
					}
					texturedPolygon(renderer, s.second.get()->collision_polygonx, s.second.get()->collision_polygony, s.second.get()->collision_polygonx.size(), s.second.get()->s.at(s.second.get()->surface_index), 0, 0, s.second.get()->x, s.second.get()->y);


					if (i.layer_light == true) {

						filledPolygonRGBA(renderer, s.second.get()->collision_polygonx, s.second.get()->collision_polygony, s.second.get()->collision_polygonx.size(), 0, 0, 0, 120, HEIGHT);
					}
				}

			}
			if (i.layer_light == true) {
				for (auto& l : i.lights) {
					raycast(lay, l.first);
				}
			}
		}
		lay++;
	}

	SDL_RenderPresent(renderer);
}

LightSource& SDLclass::find_light(string name) {
	for (auto& i : layers) {
		for (auto& l : i.lights) {
			if (name == l.first) {
				return l.second;
			}
		}
	}
	LightSource l(1, 1, 1, 1, 1, 1, 1);
	return  l;
}

LightSource::LightSource(unsigned int x, unsigned int y, int range, int intensity, Uint8 r, Uint8 b, Uint8 g) {
	LightSource::x = x;
	LightSource::y = y;
	LightSource::range = range;
	LightSource::intensity = intensity;
	LightSource::r = r;
	LightSource::b = b;
	LightSource::g = g;
}

void LightSource::teleport(int new_x, int new_y) {
	x = new_x;
	y = new_y;
}

void SDLclass::add_light_source(const string& light_name, int layer, unsigned int x, unsigned int y, int range, int intensity, Uint8 r, Uint8 b, Uint8 g) {
	if (layer > layers.size() - 1)
	{
		for (int i = layers.size() - 1; i < layer - 1; i++) {
			Layer l;
			layers.push_back(l);
		}
		Layer l;
		l.lights.insert(pair<string, LightSource>(light_name, LightSource(x, y, range, intensity, r, b, g)));
		layers.push_back(l);
	}
	else
	{
		layers.at(layer).lights.insert(pair<string, LightSource>(light_name, LightSource(x, y, range, intensity, r, b, g)));
	}
}

void SDLclass::remove_light(const string& light_name, int layer)
{
	layers.at(layer).lights.erase(light_name);
}

Sprite* SDLclass::find_sprite(string name) {
	for (auto& i : layers) {
		for (auto& l : i.sprite) {
			if (name == l.first) {
				return l.second.get();
			}
		}
	}
	return NULL;
}

template<class T>
void SDLclass::add_sprite_ptr(string name, int layer, string texture_folder_path, long double x, long double y, int w, int h) {
	T t(texture_folder_path, x, y, w, h, layer, renderer);
	shared_ptr<Sprite> p = std::make_shared<T>(t);
	if (layer >= layers.size()) {

		for (int y = layers.size(); y <= layer; y++) {
			Layer l;
			layers.push_back(l);
			add_sprite_ptr<Sprite>("light_corners", y, black_pixel_path, 0, 0, WIDTH, HEIGHT);
			
		}
		layers.at(layer).sprite.try_emplace(name, p);
	}
	else
	{
		layers.at(layer).sprite.try_emplace(name, p);
	}

}

void SDLclass::LoadSprites(string data_file_path) {
	ifstream infile(data_file_path);
	if (infile.is_open()) {
		std::string line;
		while (std::getline(infile, line))
		{

			std::stringstream iss(line);
			string l;
			vector<string> tokens;
			while (std::getline(iss, l))
			{
				std::size_t prev = 0, pos;
				while ((pos = l.find_first_of("@", prev)) != std::string::npos)
				{
					if (pos > prev)
						tokens.push_back(l.substr(prev, pos - prev));
					prev = pos + 1;
				}
				if (prev < l.length())
					tokens.push_back(l.substr(prev, std::string::npos));
			}


			if (tokens.at(0) == "Sprite") {
				add_sprite_ptr<Sprite>(tokens.at(1),stoi(tokens.at(3)),tokens.at(2), (long double)stoi(tokens.at(4)), (long double)stoi(tokens.at(5)), stoi(tokens.at(6)), stoi(tokens.at(7)));
				if (tokens.size() >= 13) {
					vector<SDL_Point> new_c;
					for (int i = 8; i < tokens.size(); i += 2) {
						new_c.push_back({ stoi(tokens.at(i)), stoi(tokens.at(i + 1)) });
					}
					layers.at(stoi(tokens.at(3))).sprite.at(tokens.at(1)).get()->change_collision_polygon(new_c);
					new_c.clear();
				}
			}
			if (tokens.at(0) == "Light") {
				add_light_source(tokens.at(1), stoi(tokens.at(2)), stoi(tokens.at(3)), stoi(tokens.at(4)), stoi(tokens.at(5)), stoi(tokens.at(6)), stoi(tokens.at(7)), stoi(tokens.at(8)), stoi(tokens.at(9)));
			}

			tokens.clear();
		}
	}
	infile.close();
}

void SDLclass::Save(string data_file_path) {


}

double CCW(SDL_Point a, SDL_Point b, SDL_Point c)
{
	return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

long double CCWp(long double ax, long double ay, long double bx, long double by, long double cx, long double cy)
{
	return (bx - ax)*(cy - ay) - (by - ay)*(cx - ax);
}

int middle(int a, int b, int c) {
	int t;
	if (a > b) {
		t = a;
		a = b;
		b = t;
	}
	if (a <= c && c <= b) return 1;
	return 0;
}
long double middlep(long double a, long double b, long double c) {
	int t;
	if (a > b) {
		t = a;
		a = b;
		b = t;
	}
	if (a <= c && c <= b) return 1;
	return 0;
}


int intersect(line a, line b) {
	if ((CCW(a.s, a.e, b.s) * CCW(a.s, a.e, b.e) < 0) &&
		(CCW(b.s, b.e, a.s) * CCW(b.s, b.e, a.e) < 0)) return 1;

	if (CCW(a.s, a.e, b.s) == 0 && middle(a.s.x, a.e.x, b.s.x) && middle(a.s.y, a.e.y, b.s.y)) return 1;
	if (CCW(a.s, a.e, b.e) == 0 && middle(a.s.x, a.e.x, b.e.x) && middle(a.s.y, a.e.y, b.e.y)) return 1;
	if (CCW(b.s, b.e, a.s) == 0 && middle(b.s.x, b.e.x, a.s.x) && middle(b.s.y, b.e.y, a.s.y)) return 1;
	if (CCW(b.s, b.e, a.e) == 0 && middle(b.s.x, b.e.x, a.e.x) && middle(b.s.y, b.e.y, a.e.y)) return 1;

	return 0;
}

int intersectp(linep a, linep b) {
	if ((CCWp(a.sx, a.sy, a.ex, a.ey, b.sx, b.sy) * CCWp(a.sx, a.sy, a.ex, a.ey, b.ex, b.ey) < 0) &&
		(CCWp(b.sx, b.sy, b.ex, b.ey, a.sx, a.sy) * CCWp(b.sx, b.sy, b.ex, b.ey, a.ex, a.ey) < 0)) return 1;

	if (CCWp(a.sx, a.sy, a.ex, a.ey, b.sx, b.sy) == 0 && middlep(a.sx, a.ex, b.sx) && middlep(a.sy, a.ey, b.sy)) return 1;
	if (CCWp(a.sx, a.sy, a.ex, a.ey, b.ex, b.ey) == 0 && middlep(a.sx, a.ex, b.ex) && middlep(a.sy, a.ey, b.ey)) return 1;
	if (CCWp(b.sx, b.sy, b.ex, b.ey, a.sx, a.sy) == 0 && middlep(b.sx, b.ex, a.sx) && middlep(b.sy, b.ey, a.sy)) return 1;
	if (CCWp(b.sx, b.sy, b.ex, b.ey, a.ex, a.ey) == 0 && middlep(b.sx, b.ex, a.ex) && middlep(b.sy, b.ey, a.ey)) return 1;

	return 0;
}

float CalculateDistance(SDL_Point p1, SDL_Point p2)
{
	float diffY = p1.y - p2.y;
	float diffX = p1.x - p2.x;
	return sqrt((diffY * diffY) + (diffX * diffX));
}

float angle(SDL_Point a, SDL_Point b) {
	return atan2(a.y - b.y, a.x - b.x) * 180 / (float)PI;
}

float slope(SDL_Point a, SDL_Point b) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return dy / dx;

}

int intercepty(SDL_Point a, SDL_Point b) {
	return a.y - slope(a, b) * a.x;

}

SDL_Point endpoint(SDL_Point a, SDL_Point b, float new_x) {
	SDL_Point end;
	end.x = new_x;
	end.y = slope(a, b)*end.x + intercepty(a, b);
	return end;
}

SDL_Point interpoint(line a, line b)
{
	// Line AB represented as a1x + b1y = c1
	double a1 = a.e.y - a.s.y;
	double b1 = a.s.x - a.e.x;
	double c1 = a1*(a.s.x) + b1*(a.s.y);

	// Line CD represented as a2x + b2y = c2
	double a2 = b.e.y - b.s.y;
	double b2 = b.s.x - b.e.x;
	double c2 = a2*(b.s.x) + b2*(b.s.y);

	double determinant = a1*b2 - a2*b1;


	SDL_Point i;
	i.x = (b2*c1 - b1*c2) / determinant;
	i.y = (a1*c2 - a2*c1) / determinant;
	return i;

}

bool shortcut(line a, Sprite s, int index) {
	line b;
	b.s.x = s.collision_polygonx[index];
	b.s.y = s.collision_polygony[index];
	if (index != s.collision_polygonx.size() - 1) {
		b.e.x = s.collision_polygonx[index + 1];
		b.e.y = s.collision_polygony[index + 1];
	}
	else
	{
		b.e.x = s.collision_polygonx[0];
		b.e.y = s.collision_polygony[0];
	}
	if (intersect(a, b) == true) {
		return true;
	}
	return false;
}

bool SDLclass::linecheck(line a, vertexstruct v, int layer) {
	bool intersections = false;
	for (auto& ss : layers.at(layer).sprite) {
		for (int vv = 0; vv < ss.second.get()->collision_polygonx.size(); vv++) {
			if (v.sprite_name == ss.first) {
				if (vv != ss.second.get()->collision_polygonx.size() - 1) {
					if (vv != v.index && vv + 1 != v.index) {
						if (intersections == true) { return true; }
						if (intersections == false) {
							intersections = shortcut(a, *ss.second.get(), vv);
						}
					}
				}
				else
				{
					if (vv != v.index && 0 != v.index) {
						if (intersections == true) { return true; }
						if (intersections == false) {
							intersections = shortcut(a, *ss.second.get(), vv);
						}
					}
				}
			}
			else
			{
				if (intersections == true) { return true; }
				if (intersections == false) {
					intersections = shortcut(a, *ss.second.get(), vv);
				}
			}
		}
	}
	return intersections;
}

void SDLclass::raycast(int layer, string light_name) {
	SDL_Point light_center{ layers.at(layer).lights.at(light_name).x ,layers.at(layer).lights.at(light_name).y };
	vector<vertexstruct> vertices, final_vertices;
	vector<long double> polygon_vertex_x, polygon_vertex_y;
	for (auto& s : layers.at(layer).sprite) {
		for (int v = 0; v < s.second.get()->collision_polygonx.size(); v++) {
			vertexstruct t;
			t.vertex.x = s.second.get()->collision_polygonx[v];
			t.vertex.y = s.second.get()->collision_polygony[v];
			t.angle = angle(light_center, t.vertex);
			t.index = v;
			t.sprite_name = s.first;
			vertices.push_back(t);
		}
	}
	std::sort(vertices.begin(), vertices.end(), [](vertexstruct val1, vertexstruct val2) {return val1.angle > val2.angle; });
	for (auto& v : vertices) {
		bool intersections = false;
		line a{ light_center,v.vertex }, b;
		intersections = linecheck(a, v, layer);
		if (intersections == false) {
			SDL_Point old_ae = a.e;
			if (a.e.x < light_center.x) {
				a.e = endpoint(light_center, a.e, -10000);
			}
			else
			{
				a.e = endpoint(light_center, a.e, 10000);
			}
			bool Loop = true;
			int intersections_finds = 0;
			vector<vertexstruct> intersection;
			map<string, shared_ptr<Sprite>>::iterator it;
			for (it = layers.at(layer).sprite.begin(); it != layers.at(layer).sprite.end() && Loop == true; it++) {
				for (int vv = 0; vv < it->second.get()->collision_polygonx.size() && Loop == true; vv++) {
					if (v.sprite_name == it->first) {
						if (vv != it->second.get()->collision_polygonx.size() - 1) {
							if (vv != v.index && vv + 1 != v.index) {
								if (shortcut(a, *it->second.get(), vv) == true) {
									if (v.sprite_name != it->first) {
										line b;
										b.s.x = it->second.get()->collision_polygonx.at(vv);
										b.s.y = it->second.get()->collision_polygony.at(vv);
										if (vv != it->second.get()->collision_polygonx.size() - 1) {
											b.e.x = it->second.get()->collision_polygonx.at(vv + 1);
											b.e.y = it->second.get()->collision_polygony.at(vv + 1);
										}
										else
										{
											b.e.x = it->second.get()->collision_polygonx[0];
											b.e.y = it->second.get()->collision_polygony[0];
										}
										vertexstruct o;
										o.vertex = interpoint(a, b);
										o.distance = CalculateDistance(light_center, o.vertex);
										o.sprite_name == v.sprite_name;
										if (!(o.vertex.x == 0 && o.vertex.y == 0)) {
											intersection.push_back(o);
											intersections_finds++;
										}
									}
									else
									{
										if (intersection.size() >= intersections_finds) {
											intersection.erase(intersection.end() - intersections_finds, intersection.end());
										}
										Loop = false;
									}
								}
							}
						}
						else
						{
							if (vv != v.index && 0 != v.index) {
								if (shortcut(a, *it->second.get(), vv) == true) {
									if (v.sprite_name != it->first) {
										line b;
										b.s.x = it->second.get()->collision_polygonx.at(vv);
										b.s.y = it->second.get()->collision_polygony.at(vv);
										if (vv != it->second.get()->collision_polygonx.size() - 1) {
											b.e.x = it->second.get()->collision_polygonx.at(vv + 1);
											b.e.y = it->second.get()->collision_polygony.at(vv + 1);
										}
										else
										{
											b.e.x = it->second.get()->collision_polygonx[0];
											b.e.y = it->second.get()->collision_polygony[0];
										}
										vertexstruct o;
										o.vertex = interpoint(a, b);
										o.distance = CalculateDistance(light_center, o.vertex);
										o.sprite_name = v.sprite_name;
										if (!(o.vertex.x == 0 && o.vertex.y == 0)) {
											intersection.push_back(o);
											intersections_finds++;
										}
									}
									else
									{
										if (intersection.size() >= intersections_finds) {
											intersection.erase(intersection.end() - intersections_finds, intersection.end());
										}
										Loop = false;
									}
								}
							}
						}
					}
					else
					{
						if (shortcut(a, *it->second.get(), vv) == true) {
							if (v.sprite_name == it->first) { break; }
							line b;
							b.s.x = it->second.get()->collision_polygonx.at(vv);
							b.s.y = it->second.get()->collision_polygony.at(vv);
							if (vv != it->second.get()->collision_polygonx.size() - 1) {
								b.e.x = it->second.get()->collision_polygonx.at(vv + 1);
								b.e.y = it->second.get()->collision_polygony.at(vv + 1);
							}
							else
							{
								b.e.x = it->second.get()->collision_polygonx[0];
								b.e.y = it->second.get()->collision_polygony[0];
							}
							vertexstruct o;
							o.vertex = interpoint(a, b);
							o.distance = CalculateDistance(light_center, o.vertex);
							o.sprite_name = it->first;
							if (!(o.vertex.x == 0 && o.vertex.y == 0)) {
								intersection.push_back(o);
								intersections_finds++;
							}
						}
					}
				}
			}
			sort(intersection.begin(), intersection.end(), [](vertexstruct v1, vertexstruct v2) {
				return v1.distance < v2.distance;
			});
			if (intersection.size() > 0) {
				a.e = intersection.at(0).vertex;
				polygon_vertex_x.push_back(a.e.x);
				polygon_vertex_y.push_back(a.e.y);
				SDL_Point aa{ polygon_vertex_x.at(polygon_vertex_x.size() - 1) ,polygon_vertex_y.at(polygon_vertex_x.size() - 1) };
				vertexstruct t;
				t.vertex = aa;
				t.sprite_name = intersection.at(0).sprite_name;
				if (final_vertices.size() > 0) {
					if (t.sprite_name == final_vertices.at(final_vertices.size() - 1).sprite_name) {



						t.angle = angle(light_center, t.vertex);
						t.priority = 1;
						final_vertices.push_back(t);
					}
					else
					{
						t.angle = angle(light_center, t.vertex);
						t.priority = 0;
						final_vertices.push_back(t);
					}
				}
				else
				{
					t.angle = angle(light_center, t.vertex);
					t.priority = 0;
					final_vertices.push_back(t);
				}
				a.e = old_ae;
				polygon_vertex_x.push_back(a.e.x);
				polygon_vertex_y.push_back(a.e.y);
				aa.x = polygon_vertex_x.at(polygon_vertex_x.size() - 1);
				aa.y = polygon_vertex_y.at(polygon_vertex_x.size() - 1);
				t.vertex = aa;
				t.angle = angle(light_center, t.vertex);
				t.sprite_name = v.sprite_name;
				if (final_vertices.at(final_vertices.size() - 1).priority == 1) {
					t.priority = 0;
				}
				else {
					t.priority = 1;

				}
				final_vertices.push_back(t);
			}
			else
			{
				a.e = old_ae;
				polygon_vertex_x.push_back(a.e.x);
				polygon_vertex_y.push_back(a.e.y);
				SDL_Point aa;
				aa.x = polygon_vertex_x.at(polygon_vertex_x.size() - 1);
				aa.y = polygon_vertex_y.at(polygon_vertex_x.size() - 1);
				vertexstruct t;
				t.vertex = aa;
				t.angle = angle(light_center, t.vertex);
				t.sprite_name = v.sprite_name;
				t.priority = 1;
				final_vertices.push_back(t);
			}
		}
	}
	vertices.clear();
	std::sort(final_vertices.begin(), final_vertices.end(), [](vertexstruct val1, vertexstruct val2) {
		if (val1.angle - val2.angle <= 0.25 && val1.angle - val2.angle >= -0.25) {
			return val1.priority < val2.priority;
		}
		else {
			return val1.angle < val2.angle;
		}
	});
	polygon_vertex_x.clear();
	polygon_vertex_y.clear();
	for (auto& v : final_vertices) {
		polygon_vertex_x.push_back(v.vertex.x);
		polygon_vertex_y.push_back(v.vertex.y);
	}
	final_vertices.clear();
	filledPolygonRGBA(renderer, polygon_vertex_x, polygon_vertex_y, polygon_vertex_x.size(), layers.at(layer).lights.at(light_name).r, layers.at(layer).lights.at(light_name).b, layers.at(layer).lights.at(light_name).g, layers.at(layer).lights.at(light_name).intensity, HEIGHT);
	polygon_vertex_x.clear();
	polygon_vertex_y.clear();
}

void SDLclass::add_element_to_group(shared_ptr<Sprite> p, string group_name) {
	Groups.at(group_name).push_back(p);
}
void SDLclass::remove_element_to_group(int index, string group_name) {
	Groups.at(group_name).erase(Groups.at(group_name).begin() + index);
}

bool rect_collision(SDL_Rect a, SDL_Rect b) {
	return !(a.x > b.x + b.w || a.x + a.w < b.x || a.y > b.y + b.h || a.y + a.h < b.y);
}

bool Polygon_point::is_left() {
	return x < succ->x;
}

Segment Polygon_point::line() {
	return{ { x,y },{ succ->x, succ->y } };
}

bool operator==(Polygon_point a, Polygon_point b) {
	return a.x == b.x && a.y == b.y && a.succ == b.succ;
}

bool operator==(Segment a, Segment b) {
	return (a.a == b.a && a.b == b.b) || (a.a == b.b && a.b == b.a);
}

bool operator<(Segment a, Segment b) {
	return a.a.y < b.a.y;
}

bool point_inside_polygon(Polygon_point point, const Sprite& polygon) {
	Segment s{ { -10e9, -10e9 }, point };
	int count{};
	for (int i{}; i < polygon.collision_polygonx.size(); ++i) {
		if (i != polygon.collision_polygonx.size() - 1) {
			if (intersectp({  polygon.collision_polygonx[i], polygon.collision_polygony[i] , polygon.collision_polygonx[i + 1], polygon.collision_polygony[i + 1] }, s))
				count++;
		}
		else {
			if (intersectp({ polygon.collision_polygonx[i], polygon.collision_polygony[i] , polygon.collision_polygonx[0], polygon.collision_polygony[0] } , s))
				count++;
		}
	}
	return count % 2;
}

bool polygon_collision(const Sprite& a, const Sprite& b) {
	if (point_inside_polygon({ a.collision_polygonx[0], a.collision_polygony[0] }, b) || point_inside_polygon({ b.collision_polygonx[0], b.collision_polygony[0] }, a))
		return true;
	vector<Polygon_point> points;

	int i{};
	for (; i < a.collision_polygonx.size(); ++i) {
		points.push_back({ a.collision_polygonx[i], a.collision_polygony[i] });
		if (i != 0)
			points[i - 1].succ = &points[i];
		else if (i == a.collision_polygonx.size() - 1)
			points[i].succ = &points[0];
	}
	for (; i < b.collision_polygonx.size(); ++i) {
		points.push_back({ b.collision_polygonx[i], b.collision_polygony[i] });
		if (i != a.collision_polygonx.size())
			points[i - 1].succ = &points[i];
		else if (i == a.collision_polygonx.size() + b.collision_polygonx.size() - 1)
			points[i].succ = &points[a.collision_polygonx.size()];
	}
	sort(points.begin(), points.end(), [](Polygon_point a, Polygon_point b) {return a.x < b.x; });
	set<Segment> lines;
	for (int i{}; i < a.collision_polygonx.size() + b.collision_polygonx.size(); ++i) {
		if (points[i].is_left()) {
			lines.insert(points[i].line());
			auto current_line{ lines.find(points[i].line()) };
			if (current_line != lines.begin()) {
				if (intersectp(points[i].line(), *prev(current_line)))//ERRORE QUA
					return true;
			}
			if (current_line != prev(lines.end())) {
				if (intersectp(points[i].line(), *(next(current_line))))
					return true;
			}
		}
		else {
			auto current_line{ lines.find(points[i].line()) };
			if (current_line != lines.begin() && current_line != prev(lines.end())) {
				if (intersectp(*(prev(current_line)), *(next(current_line))))
					return true;
			}
			lines.erase(points[i].line());
		}
	}
	return false;
}
