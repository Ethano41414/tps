#include "code.h"
#include "teZZt.h"

// NE PAS COMMENTER CETTE LIGNE
BEGIN_TEST_GROUP(code)



TEST(identification_avec_enum) {
	CHECK(   ID == identification("x"));
	CHECK( NONE == identification("x\n"));
	CHECK(  SIN == identification("sin(x)"));
	CHECK(  COS == identification("cos(x)"));
	CHECK(  LOG == identification("log(x)"));
	CHECK(  EXP == identification("exp(x)"));
	CHECK( NONE == identification("t"));
}


TEST(control_eval_f) {
   CHECK( EQ( 0.0, evalf( 0.0, ID)));
   CHECK( EQ( 0.0, evalf( 0.0, SIN)));
   CHECK( EQ( 1.0, evalf( 0.0, COS)));
   CHECK( EQ( 1.0, evalf( 0.0, EXP)));

   CHECK( EQ(      M_PI , evalf( M_PI, ID)));
   CHECK( EQ(       0.0 , evalf( M_PI, SIN)));
   CHECK( EQ(      -1.0 , evalf( M_PI, COS)));
   CHECK( EQ( exp(M_PI) , evalf( M_PI, EXP)));

   CHECK( EQ( 0.0 , evalf( M_PI/2.0, COS)));
}

// NE PAS COMMENTER CETTE LIGNE
END_TEST_GROUP(code)

// NE PAS COMMENTER CETTE FONCTION
// execute tous les tests
int main(void) {
	RUN_TEST_GROUP(code); 
 	return 0;
}
