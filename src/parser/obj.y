%token VERTEX FACE TEXTURE NORMAL ID NUMBER SLASH

%union
{
    int id;
    float value;
}

%{
#include "obj.hh"

#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char *s) { }
extern FILE *yyin;
%}

%%
obj: /* empty */
|   obj vertex
|   obj texture
|   obj face
|   obj normal;

vertex:
    VERTEX NUMBER NUMBER NUMBER
    {
        printf("v %f %f %f\n", $<value>2, $<value>3, $<value>4);
        addVertex($<value>2, $<value>3, $<value>4);
    };

texture:
    TEXTURE NUMBER NUMBER
    {
        printf("vt %f %f\n", $<value>2, $<value>3);
        addTexture($<value>2, $<value>3);
    };

normal:
    NORMAL NUMBER NUMBER NUMBER
    {
        printf("vn %f %f %f\n", $<value>2, $<value>3, $<value>4);
        addNormal($<value>2, $<value>3, $<value>4);
    };

face:
    simpleface
|   textureface
|   normalface
|   fullface;

simpleface:
    FACE ID ID ID
    {
        printf("f %d %d %d\n", $<id>2, $<id>3, $<id>4);
        addFace($<id>2, $<id>3, $<id>4);
    };

textureface:
    FACE ID SLASH ID ID SLASH ID ID SLASH ID
    {
        printf("f %d/%d %d/%d %d/%d\n", $<id>2, $<id>4, $<id>5, $<id>7, $<id>8, $<id>10);
        addFaceWithTexture($<id>2, $<id>5, $<id>8, $<id>4, $<id>7, $<id>10);
    };

normalface:
    FACE ID SLASH SLASH ID ID SLASH SLASH ID ID SLASH SLASH ID
    {
        printf("f %d//%d %d//%d %d//%d\n", $<id>2, $<id>5, $<id>6, $<id>9, $<id>10, $<id>13);
        addFaceWithNormal($<id>2, $<id>6, $<id>10, $<id>5, $<id>9, $<id>13);
    };

fullface:
    FACE ID SLASH ID SLASH ID ID SLASH ID SLASH ID ID SLASH ID SLASH ID
    {
        printf("f %d/%d/%d %d/%d/%d %d/%d/%d\n", $<id>2, $<id>4, $<id>6, $<id>7, $<id>9, $<id>11, $<id>12, $<id>14, $<id>16);
        addFaceWithTextureAndNormal($<id>2, $<id>7, $<id>12, $<id>4, $<id>9, $<id>14, $<id>6, $<id>11, $<id>16);
    };
%%

void parseFile(const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error: could not open file %s\n", fileName);
        return;
    }

    yyin = file;
    initParser();
    yyparse();
    fclose(file);
}