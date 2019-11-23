#pragma once

#include <fstream>
#include <string>
#include <iostream>

#include "DotVisitor.h"
#include "MiniJavaScanner.h"
using std::ifstream;
using std::ofstream;
using std::cout;
using std::string;


std::string readFile(std::string fileName);

void test(const string& filename, bool is_null=false);

void test(const string& filename, DotVisitor* visitor, bool is_null=false);