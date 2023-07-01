#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct IrisInformation
{
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    char *class;
};

struct IrisInformationArrays
{
    char *atributos[5];
    double caracteristicas[150][4];
    char *class[150];
};

const int DATA_SIZE = 150;
struct IrisInformationArrays *getDataFrom(const char *path);
void printMenu(void);

int main()
{
    const char *path = "../database/iris.csv";
    struct IrisInformationArrays *dataArrays = getDataFrom(path);
    // Assume-se que foram obtidos os dados
    int resposta;
    while (resposta != 3)
    {
        if (resposta < 0 || resposta > 3)
        {
            printf("------------------------\nOpção inválida.\n------------------------\n");
        }
        else if (resposta == 1)
        {
            printf("Working on it\n");
        }
        else if (resposta == 2)
        {
            printf("Working on it\n");
        }
        printMenu();
        scanf("%d", &resposta);
    }

    // Freeing allocated memory
    for (int j = 0; j < DATA_SIZE; j++)
    {
        free(dataArrays->class[j]);
    }
    free(dataArrays);

    return 0;
}

struct IrisInformationArrays *getDataFrom(const char *path)
{
    struct IrisInformation *data = malloc(DATA_SIZE * sizeof(struct IrisInformation));
    if (data == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        exit(1);
    }

    char *line = malloc(100 * sizeof(char));
    fgets(line, 100, file); // skipping column name line

    int i = 0;
    while (fgets(line, 100, file) != NULL)
    {
        struct IrisInformation iris;
        char *token = strtok(line, ",");
        iris.sepal_length = atof(token);
        token = strtok(NULL, ",");
        iris.sepal_width = atof(token);
        token = strtok(NULL, ",");
        iris.petal_length = atof(token);
        token = strtok(NULL, ",");
        iris.petal_width = atof(token);
        token = strtok(NULL, ",");
        iris.class = malloc(strlen(token) + 1); // +1 for null terminator
        strcpy(iris.class, token);

        data[i] = iris;
        i++;
    }

    fclose(file);
    free(line);

    struct IrisInformationArrays *arrays = malloc(sizeof(struct IrisInformationArrays));
    if (arrays == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < DATA_SIZE; i++)
    {
        arrays->caracteristicas[i][0] = data[i].sepal_length;
        arrays->caracteristicas[i][1] = data[i].sepal_width;
        arrays->caracteristicas[i][2] = data[i].petal_length;
        arrays->caracteristicas[i][3] = data[i].petal_width;
        arrays->class[i] = data[i].class;
    }

    arrays->atributos[0] = "sepal_length";
    arrays->atributos[1] = "sepal_width";
    arrays->atributos[2] = "petal_length";
    arrays->atributos[3] = "petal_width";
    arrays->atributos[4] = "class";

    return arrays;
}

void printMenu(void)
{
    printf("\n\n\n------------------------------\n");
    printf("[1] – Mostrar estatísticas\n\n[2] – Classificar amostra\n\n[3] – Sair\n\n");
    printf("------------------------------\n\n\n");
}