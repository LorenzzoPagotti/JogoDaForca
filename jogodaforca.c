// Feito por Lorenzzo Pagotti.
// https://github.com/LorenzzoPagotti


#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define TAMANHO_PALAVRA 20

void abertura();
void chuta();
void desenhaforca();
void escolhepalavra();
int enforcou ();
int acertou ();
int jachutou(char letra);
void adicionapalavra();
int chuteserrados ();

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura() 
{
	printf("****************\n");
	printf(" Jogo da Forca *\n");
	printf("****************\n\n");
}

void mensagemacertou ()
{
    printf("            .-=========-.            \n");
    printf("            '-=======-'             \n");
    printf("            _|   .=.   |_            \n");
    printf("           ((|  {{1}}  |))           \n");
    printf("            \\|   /|\\   |/            \n");
    printf("             \\__ '`' __/             \n");
    printf("               _`) (`_               \n");
    printf("             _/_______\\_             \n");
    printf("            /___________\\            \n\n");

	printf("Voce acertou! Parabens!\n");
	printf ("A palavra secreta era: %s\n\n", palavrasecreta);
}

void mensagemerrou ()
{

	printf("\n");

    printf("           ______\n");
    printf("        .-\"      \"-.\n");
    printf("       /            \\\n");
    printf("      |              |\n");
    printf("      |,  .-.  .-.  ,|\n");
    printf("      | )(__/  \\__)( |\n");
    printf("      |/     /\\     \\|\n");
    printf("      (_     ^^     _)\n");
    printf("       \\__|IIIIII|__/\n");
    printf("        | \\IIIIII/ |\n");
    printf("        \\          /\n");
    printf("      	 `--------`\n");

	printf("Voce perdeu!\n");
	printf ("A palavra secreta era: %s\n\n", palavrasecreta);

}

void chuta() 
{
	char chute;
	printf("Qual letra? ");
	scanf(" %c", &chute);

	chutes[chutesdados] = chute;
	chutesdados++;
}

void desenhaforca()
{
	int erros = chuteserrados();

	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (erros>=1 ? '(' : ' '), (erros>=1 ? '_' : ' '), (erros>=1 ? ')' : ' '));
	printf(" |      %c%c%c  \n", (erros>=3 ? '\\' : ' '), (erros>=2 ? '|' : ' '), (erros>=3 ? '/' : ' '));
	printf(" |       %c     \n", (erros>=2 ? '|' : ' '));
	printf(" |      %c %c   \n", (erros>=4 ? '/' : ' '), (erros>=4 ? '\\' : ' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");

	if (chutesdados == 0)
	{
		printf("Boa sorte!\nPrimeira tentativa\n", chutesdados);
	}
	else if (chutesdados == 1)
	{
	printf("Voce ja deu 1 chute\n");
	}
	else 
	{
		printf("Voce ja deu %d chutes\n", chutesdados);
	}
	for(int i = 0; i < strlen(palavrasecreta); i++) 
    {
		if(jachutou(palavrasecreta[i])) 
        {
			printf("%c ", palavrasecreta[i]);
		} 
        else 
        {
			printf("_ ");
		}
	}
	printf("\n");
}

void adicionapalavra() {
    char quer;

    printf("Voce quer adicionar uma nova palavra no jogo (S/N)? ");
    scanf(" %c", &quer);

    if(quer == 'S') {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Digite a sua nova palavra, em Caps Lock: ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) 
		{
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;

        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
}

void escolhepalavra() 
{
	FILE* f;

	f = fopen("palavras.txt", "r");
	
	if(f == 0) 
	{
		printf("Palavras nao disponiveis.\n\n");
		exit(1);
	}

	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);

	srand(time(0));
	int aleatorio = rand() % qtddepalavras;

	for(int i = 0; i <= aleatorio; i++) 
	{
		fscanf(f, "%s", palavrasecreta);
	}
	fclose(f);
}

int chuteserrados ()
{
	int erros = 0;
	for (int i = 0 ; i < chutesdados ; i++)
	{
		int existe = 0;
		for (int j = 0 ; j < strlen(palavrasecreta) ; j++)
		{
			if (chutes[i] == palavrasecreta[j])
			{
				existe = 1;
				break;
			}
		}
			if (!existe) erros++;
	}

	return erros;
}

int enforcou ()
{
	return chuteserrados() >= 5;
}

int acertou ()
{
	for (int i = 0 ; i < strlen(palavrasecreta) ; i++)
	{
		if (!jachutou (palavrasecreta[i])) 
		{
			return 0;
		}
	}
	return 1;
}

int jachutou(char letra) 
{
	int achou = 0;
	for(int j = 0; j < chutesdados; j++) 
    {
		if(chutes[j] == letra) 
        {
			achou = 1;
			break;
		}
	}

	return achou;
}

int main() 
{
	escolhepalavra();
	abertura();

	do 
    {

		desenhaforca();
		chuta();

	} while (!acertou() && !enforcou());

	if (acertou())
	{
		mensagemacertou();
	}
	else
	{
		mensagemerrou();
	}

	adicionapalavra();

}