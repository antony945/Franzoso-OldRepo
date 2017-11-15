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
		s.at(index) = NULL;
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


	s.at(index) = rz_dst;
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
