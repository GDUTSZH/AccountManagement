

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <string>

#include "cencode.h"
#include "cdecode.h"

using namespace std;

/* arbitrary buffer size */
#define SIZE 100

string Base64Encode(string sInput);

string Base64Decode(string sInput);