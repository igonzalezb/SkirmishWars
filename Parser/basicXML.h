#pragma once

extern "C"{
#include <expat.h>
};
#include "Resources.h"

#define BUFF_LEN	10000	//1 000

void readFileToBuffer(XML_Parser P, FILE * fp);

void startTagCallback(void *userData, const XML_Char *name, const XML_Char **atts);

void endTagCallback(void *userData, const XML_Char *name);

void chararacterDataCallback(void *userData, const XML_Char *s, int len);

