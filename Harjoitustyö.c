#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define WORDCHUNK 20
#define n 999999

/** Valtteri Kinnunen 2477767 */

struct binaaripuu {
  struct binaaripuu *vasen; /* Sanat, jotka ovat vasemmalla puolella puun solmua*/
  struct binaaripuu *oikea; /* Sanat, jotka ovat oikealla puolella puun solmua */
  char *sana;
  int kaytetty;
};

struct Sanat{
	char *psana;
	long kerrat
};
int i = 0;
struct Sanat uusiTaulu[n];


/* compare funktio qsortia varten */
int compare (const void *a, const void *b){

	return (((struct Sanat*)b)->kerrat - ((struct Sanat*)a)->kerrat);
}

char *hankiSana(FILE *input){
  char *temp = NULL;
  int laskuri; /* laskee merkkien lukumäärän, joita muistivarauksessa on*/
  int byte;
  int sanamaara; /* muistivarauksen merkkien määrä*/

  /* Hypätään yli ensimmäiset ei-aakkoselliset merkit, jotka tulevat vastaan */
  for (byte = fgetc(input); !isalpha(byte); byte = fgetc(input)){
    if (byte == EOF)
      return NULL;
  }
  /* Varataan sanalle vaadittava tila */
  if ((temp = malloc(sanamaara = WORDCHUNK)) == NULL)
    return NULL;

  /* aloitetaan tavujen kerääminen */
  for (laskuri = 0; isalpha(byte) ; byte = fgetc(input)){
    if (laskuri == sanamaara-1){

	char *temp2;

	if ((temp2 = realloc(temp,sanamaara+=WORDCHUNK)) == NULL)

	return NULL;

	else
	temp = temp2;
    }
    byte = tolower (byte);
    *(temp+laskuri++) = byte;

  }

  *(temp+laskuri) = 0;

  ungetc(byte,input);
  return temp;
}

/*
Char pointer stringiin, joka aiotaan lisätä.
Struct binaaripuu osoittaa juurisolmuun.
lisaaSana palauttaa intin, joka osoittaa, kuinka monta sanaa lisätään.
*/
int lisaaSana (char *teksti, struct binaaripuu **base){

	struct binaaripuu *temp;
	int suunta;

	/* Varataan tilaa uudelle solmulle*/
	if((temp = malloc(sizeof *temp)) == NULL)
		return 0;

	/* Asetetaan solmulle arvot*/
	temp->vasen = temp->oikea = NULL;
	temp->sana = teksti;
	temp->kaytetty = 1;

	/* Laitetaan sana oikealle paikalleen binääripuussa*/
	if (*base == NULL)
	*base = temp; /** Jos sanoja ei ole vielä asetettu, tehdään uusi solmu*/
	else{
		struct binaaripuu *prev = NULL, *this = *base;
		int suunta;

		/* etsitään solmu, jonka tulisi osoittaa tähän solmuun*/
		while (this != NULL){
			prev = this;

			if ((suunta = strcmp(this->sana, temp->sana)) == 0){

				/* Sana on jo puussa, palautetaan 0*/
				this->kaytetty += 1;
				free(temp);
				return 0;
			}
			else
				if (suunta <= 0) /* Uusi sana on entisen sanan oikealla*/
					this = this->oikea;
				else /* Uusi sana on entisen sanan vasemmalla*/
					this = this->vasen;
		}
		if (suunta < 0)
			prev->oikea = temp;
		else
			prev->vasen = temp;
	}
	return 1;

}

/*
poistaSana funktio poistaa rekursiivisesti tietyn struct binaaripuun solmun ja ne solmut, jotka on linkitetty siihen.
Jos trace parametri ei ole nolla, funktio tulostaa käytetyn sanan ja kuinka monta kertaa sana ilmeni.
*/
void poistaSana(struct binaaripuu *juuri, int trace) {
	if (juuri == NULL) return;

	poistaSana(juuri->vasen,trace);
	if (trace){
	uusiTaulu[i].psana = malloc(sizeof(juuri->sana));
	uusiTaulu[i].psana = juuri->sana;
	uusiTaulu[i].kerrat = juuri->kaytetty;
	i++;
	poistaSana(juuri->oikea,trace);
	}
}

/*
kaikkiSanat yhdistää kolme aikaisempaa funktiota keskenään.
hankiSana funktio hakee yksittäisiä sanoja tiedostosta, lisaaSana lisää sanan puuhun.
poistaSana poistaa sanan sekä ilmoittaa sanan esiintymiskerrat annetussa tiedostossa.
*/
unsigned long kaikkiSanat (FILE *input, int trace){

	int l = 0;
	int m = 0;

	struct binaaripuu *juuri = NULL;
	char *merkkipointer;
	unsigned long sanamaara = 0;

	clock_t t1 = clock();
	while ((merkkipointer = hankiSana(input)) !=NULL)
	sanamaara += lisaaSana(merkkipointer, &juuri);
	poistaSana(juuri,trace);
	qsort((void *) uusiTaulu, sanamaara, sizeof(uusiTaulu[0]), compare);
	while ( l<100){
	printf( "%d" " Sana \"%s\" ilmeni %lu kertaa\n", l+1, uusiTaulu [l].psana, uusiTaulu[l].kerrat);
	l++;
	}
	t1 = clock() - t1;
	double fulltime = ((double)t1)/CLOCKS_PER_SEC;
	printf("\nOhjelmalta meni %f sekuntia suorittamiseen\n", fulltime);
	return sanamaara;

}

usage (char *nimi, char *teksti){
	fprintf(stderr, "Ohjelman kaytto: %s [[-v] filename]\n", nimi);
	if (teksti != NULL) fprintf(stderr, "		%s\n" ,teksti);

	return EXIT_FAILURE;
}


/* main-funktio */
int main(int argc, char *argv[]){

  FILE *input;
  unsigned trace = 0;

  switch (argc){
    case 1:
		trace = 1;
		printf ("Anna tiedoston nimi: ");
		char tiedosto [50];
		scanf ("%s", tiedosto);
		if (input = fopen(tiedosto, "r")) {
			  printf("Tiedostossa oli %lu erilaista sanaa\n", kaikkiSanat(input,trace));

		if (input != stdin) fclose(input);
		}
		if (input == NULL){
		printf("Tiedostoa ei loydy");
		}
    	break;

    case 2:
      if  (strcmp("-v",argv[1]) == 0){
        trace = 1;
        input = stdin;
        printf("Tiedostossa oli %lu erilaista sanaa\n", kaikkiSanat(input,trace));
		if (input != stdin) fclose(input);
      }
      else
      {
        trace = 0;
        if ((input = fopen(argv[1],"r")) == NULL)
          return usage(argv[0],"Tiedostoa ei ole");
      }
      break;

    case 3:
      if (strcmp("-v",argv[1]) == 0){
        trace = 1;
        printf("Tiedostossa oli %lu erilaista sanaa\n", kaikkiSanat(input,trace));
		if (input != stdin) fclose(input);
        if ((input = fopen(argv[2],"r")) == NULL)
          return usage(argv[0],"Tiedostoa ei ole");
      }
      else
        return usage(argv[0],NULL);
      break;

    default:
      return usage(argv[0],NULL);
      break;
  }



  return EXIT_SUCCESS;
}

