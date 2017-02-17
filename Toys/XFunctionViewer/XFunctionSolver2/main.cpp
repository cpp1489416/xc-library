#include <iostream>
#include <cstdio>
#include "BasicParseNodes\XPlusParseNode.h"
#include "XFunctionParser.h"

using namespace std;

double f(double x)
{
    return sin(x);
}

double dx(double x)
{
    return cos(x);
}

int main()
{
    //freopen("C:\\Users\\Fox\\Desktop\\in.txt", "r", stdin);

    //string str = "cos(x + y * z) + cos(65)";
    //
    //while (true) {
    //    XFunctionParser parser;
    //    XFunctionParser diffParser;
    //    getline(cin, str);
    //    parser.setSource(str);

    //    cout << "Infix: " << parser.getInfixExpression() << endl;
    //    cout << "Polish: " << parser.getReversePolishExpression() << endl;
    //    cout << "getDifferentiate \"x\":\n";
    //    parser.getDifferentiate(diffParser, "x");
    //    cout << "Infix: " << diffParser.getInfixExpression() << endl;
    //    cout << "Polish: " << diffParser.getReversePolishExpression() << endl;
    //    cout << "getDifferentiate \"y\":\n";
    //    parser.getDifferentiate(diffParser, "y");
    //    cout << "Infix: " << diffParser.getInfixExpression() << endl;
    //    cout << "Polish: " << diffParser.getReversePolishExpression() << endl;
    //    for (int i = 0; i < 1000; i++) {
    //        for (int j = 0; j < 1000; j++) {

    //           cout << "x = " << i << ", y = " << j << ", value = " << parser.getFunction(i, j) << endl;
    //        }
    //    }
    //}

    XFunctionParser parser;
    parser.setSource("y - ~x");
    cout << parser.getInfixExpression();

 //   double x = -1;
 //   int times = 10;
	//for (double t = -10; t <= 100; t += 0.1) {
	//	double x = t;
	//	for (int i = 0; i < 1; i++) {
	//		x = x - f(x) / dx(x);
	//	}
	//	if (fabs(x - t) < 0.1) {
	//		cout << t << " " << sin(t) << " " << sin(x) << endl;
	//	}
	//	// cout << t << " " << x << endl;
	//}

    system("Pause");

    return 0;
}

