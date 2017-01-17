#include <iostream>

void missionari_e_cannibali(char barca_in, int cann_in, int miss_in);
// pull request
int main()
{
  std::cout << "Verrà mostrato lo stato iniziale con uno schema che lo rapprensenta e una lista di possibili passaggi." << std::endl << std::endl;
  //mostra la legenda dello schema:
  std::cout << "C = Cannibale" << std::endl << "M = Missionario" << std::endl << "B = Barca" << std::endl;
  //definizione delle variabili che indicano lo stato iniziale
  char barca_in = 'D';
  int cann_in = 3, miss_in = 3;
  missionari_e_cannibali(barca_in, cann_in, miss_in);
}

void missionari_e_cannibali(char barca_in, int cann_in, int miss_in)
{
  if(cann_in != 0 || miss_in != 0)
  {
    if(miss_in == 3 || miss_in == 0 || cann_in - miss_in == 0)
    {
      std::cout << std::endl;
      //mostra uno schema che illusra la situazione corrente:
      for(int i = 0; i < 3 - cann_in; i++)
      {
        std::cout << "C";
      }
      for(int i = 0; i < 3 - miss_in; i++)
      {
        std::cout << "M";
      }
      if(barca_in == 'S')
      {
        std::cout << " B        ";
      }
      else
      {
        std::cout << "        B ";
      }
      for(int i = 0; i < cann_in; i++)
      {
        std::cout << "C";
      }
      for(int i = 0; i < miss_in; i++)
      {
        std::cout << "M";
      }
      std::cout << std::endl << std::endl;
      //scrive la situazione corrente:
      std::cout << "S" << barca_in << ";" << cann_in << "," << miss_in << std::endl << std::endl;
      /*dalla situazione iniziale possono essere fatte al massimo 5 diverse azioni:
      a) far attraversare 1 cannibale
      b) far attraversare 1 missionario
      c) far attraversare 1 missionario e 1 cannibale
      d) far attraversare 2 cannibali
      e) far attraversare 2 missionari*/
      int cann_a, cann_b, cann_c, cann_d, cann_e; //numero di cannibali sulla riva destra in ognuno dei 5 casi elencati
      int miss_a, miss_b, miss_c, miss_d, miss_e; //numero di missionari sulla riva destra in ognuno dei 5 casi elencati
      char barca_out;    //posizione della barca in output (è sempre la riva opposta a quella di partenza)
      std::cout << "Possibili passaggi successivi:" << std::endl;
      int n_out = 1;   //indica il numero del possibile passaggio; viene usato nell'output
      int ID_a = 0, ID_b = 0, ID_c = 0, ID_d = 0; //indicano il numero che l'utente dovrà scrivere per selezionare un caso
      //ora analizza i dati per verificare quali azioni è possibile svolgere, assegna i valori alle variabili prima dichiarate
      //e scrive sulla console i possibili passaggi successivi
      if(barca_in == 'D')
      {
        barca_out = 'S';
        if(cann_in > 0)
        {
          //caso a:
          cann_a = cann_in - 1;
          miss_a = miss_in;
          std::cout << n_out << ") S" << barca_out << ";" << cann_a << "," << miss_a << std::endl; //dà un output come: "1) SD;3,3"
          ID_a = n_out;
          n_out++;
        }
        if(miss_in > 0)
        {
          //caso b:
          cann_b = cann_in;
          miss_b = miss_in - 1;
          std::cout << n_out << ") S" << barca_out << ";" << cann_b << "," << miss_b << std::endl;
          ID_b = n_out;
          n_out++;
          if(cann_in > 0)
          {
            //caso c:
            cann_c = cann_in - 1;
            miss_c = miss_in - 1;
            std::cout << n_out << ") S" << barca_out << ";" << cann_c << "," << miss_c << std::endl;
            ID_c = n_out;
            n_out++;
          }
        }
        if(cann_in > 1)
        {
          //caso d:
          cann_d = cann_in - 2;
          miss_d = miss_in;
          std::cout << n_out << ") S" << barca_out << ";" << cann_d << "," << miss_d << std::endl;
          ID_d = n_out;
          n_out++;
        }
        if(miss_in > 1)
        {
          //caso e:
          cann_e = cann_in;
          miss_e = miss_in - 2;
          std::cout << n_out << ") S" << barca_out << ";" << cann_e << "," << miss_e << std::endl;
          n_out++;
        }
      }
      else
      {
        barca_out = 'D';
        if(cann_in < 3)
        {
          //caso a:
          cann_a = cann_in + 1;
          miss_a = miss_in;
          std::cout << n_out << ") S" << barca_out << ";" << cann_a << "," << miss_a << std::endl;
          ID_a = n_out;
          n_out++;
        }
        if(miss_in < 3)
        {
          //caso b:
          cann_b = cann_in;
          miss_b = miss_in + 1;
          std::cout << n_out << ") S" << barca_out << ";" << cann_b << "," << miss_b << std::endl;
          ID_b = n_out;
          n_out++;
          if(cann_in < 3)
          {
            //caso c:
            cann_c = cann_in + 1;
            miss_c = miss_in + 1;
            std::cout << n_out << ") S" << barca_out << ";" << cann_c << "," << miss_c << std::endl;
            ID_c = n_out;
            n_out++;
          }
        }
        if(cann_in < 2)
        {
          //caso d:
          cann_d = cann_in + 2;
          miss_d = miss_in;
          std::cout << n_out << ") S" << barca_out << ";" << cann_d << "," << miss_d << std::endl;
          ID_d = n_out;
          n_out++;
        }
        if(miss_in < 2)
        {
          //caso e:
          cann_e = cann_in;
          miss_e = miss_in + 2;
          std::cout << n_out << ") S" << barca_out << ";" << cann_e << "," << miss_e << std::endl;
          n_out++;
        }
      }
      int ID_in; //il numero del passaggio scelto
      std::cout << std::endl << "Inserire il numero del passaggio scelto: ";
      std::cin >> ID_in;
      while(ID_in >= n_out || ID_in < 1)
      {
        std::cout << "Numero non valido. Riprovare: ";
        std::cin >> ID_in;
      }
      if(ID_in == ID_a)
      {
        missionari_e_cannibali(barca_out, cann_a, miss_a);
      }
      else
      {
        if(ID_in == ID_b)
        {
          missionari_e_cannibali(barca_out, cann_b, miss_b);
        }
        else
        {
          if(ID_in == ID_c)
          {
            missionari_e_cannibali(barca_out, cann_c, miss_c);
          }
          else
          {
            if(ID_in == ID_d)
            {
              missionari_e_cannibali(barca_out, cann_d, miss_d);
            }
            else
            {
              missionari_e_cannibali(barca_out, cann_e, miss_e);
            }
          }
        }
      }
    }
    else
    {
      std::cout << "Hai perso!";
    }
  }
  else
  {
    std::cout << "Hai vint0000000000000000o!";
  }
}
