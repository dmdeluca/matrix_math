#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

struct fraction {
	int numerator;
	int denominator;
};

typedef struct fraction Fraction;

struct matrix {
	int rows;
	int cols;
	Fraction * matrix_data;
};

typedef struct matrix Matrix;



enum FractionParseState {
	GETTING_NUMERATOR,
	GETTING_DENOMINATOR,
	BETWEEN_FRACTIONS
};

enum UserChoice {
	UNDECIDED,
	MULTIPLY,
	ADD,
	SUBTRACT,
	//COMPUTE_FN,
	FIND_DETERMINANT,
	FIND_INVERSE,
	REDUCE_FRACTION,
	ADD_FRACTIONS,
	SUB_FRACTIONS,
	MUL_FRACTIONS,
	DIV_FRACTIONS,
	QUIT,
	END
};

const char * menuOptionText[ ] = {
	"Undecided",
	"Multiply matrices",
	"Add matrices",
	"Subtract matrices",
	//"Compute f^n",
	"Find determinant",
	"Find inverse",
	"Reduce fraction",
	"Add fractions",
	"Subtract fractions",
	"Multiply fractions",
	"Divide fractions",
	"Quit program"
};

/*
==================
== DECLARATIONS ==
==================
*/
Matrix	* createMatrix2D(int n, int m);
Matrix	* userCreateMatrix( );
Matrix	* userFillMatrix(Matrix * pMatrix);
int		getUserChoice(void);
Fraction		findDeterminant(Matrix * pMatrix);
int		setSubmatrixValues(int matrixIndex, Matrix * pSubmatrix, Matrix * pMatrix);
double	* fillZero(Fraction * dArray, int n, int m);
int		countDigitsf(double _number);
void	destroyMatrix2D(Matrix * pMatrix);
void	multiplyMatrices2D(Matrix * pMatrixA, Matrix * pMatrixB);
void	addMatrices2D(Matrix * pMatrixA, Matrix * pMatrixB, int doSubtract);
Fraction	matrixCellProduct(Matrix * pMatrixA, Matrix * pMatrixB, int row, int col);
void	printMatrix(Matrix * pMatrix);
void	clearKeyboardBuffer(void);
void	printMenu(void);
int		getIntBounded(int lower_bound, int upper_bound, int inclusive);
int		getMostDigits(Matrix * pMatrix);
int		countDigits(int _integer);
void	doMatrixMultiplication( );
void	doMatrixAddition();
void	doMatrixSubtraction( );
void	doFindDeterminant( );
void	doFindInverse( );
void	doReduceFraction( );
void	doAddFractions( );
void	doSubFractions( );
void	doMulFractions( );
void	doDivFractions( );
void	doQuit( );
int fractionLength(Fraction pFraction);
void	doMenuErrorMessage( );
void	negativeMatrix(Matrix * pMatrix);
Fraction	fractionSum(Fraction fractionA, Fraction fractionB);
Fraction	fractionDifference(Fraction fractionA, Fraction fractionB);
Fraction	fractionProduct(Fraction fractionA, Fraction fractionB);
Fraction	fractionQuotient(Fraction fractionA, Fraction fractionB);
int		reduceFraction(Fraction * pFraction);
void	printFraction(Fraction pFraction);
int		commonFactor(int n, int d);
//void	doComputeFN( );
Fraction makeFrac( int,int);

/*
==================
== MAIN PROGRAM ==
==================
*/
int main(int argc, char * argv[ ]) {

	int user_choice;

	user_choice = UNDECIDED;

	while ( user_choice != QUIT ) {
		printMenu( );
		printf("Please choose an option: ");
		switch ( user_choice = getUserChoice( ) ) {
		case MULTIPLY:
			doMatrixMultiplication( );
			break;
		case ADD:
			doMatrixAddition( );
			break;
		case SUBTRACT:
			doMatrixSubtraction( );
			break;
			/*
		case COMPUTE_FN:
			doComputeFN( );
			break;
			*/
		case FIND_DETERMINANT:
			doFindDeterminant( );
			break;
		case FIND_INVERSE:
			doFindInverse( );
			break;
		case REDUCE_FRACTION:
			doReduceFraction( );
			break;
		case ADD_FRACTIONS:
			doAddFractions( );
			break;
		case SUB_FRACTIONS:
			doSubFractions( );
			break;
		case MUL_FRACTIONS:
			doMulFractions( );
			break;
		case DIV_FRACTIONS:
			doDivFractions( );
			break;
		case QUIT:
			doQuit( );
			break;
		default:
			doMenuErrorMessage( );
			clearKeyboardBuffer( );
			break;
		}
	}

	return 0;
}

/*
initialize and return a fraction
*/
Fraction makeFrac(int numerator, int denominator) {
	Fraction returnFraction = { numerator, denominator };
	return returnFraction;
}



/*
procedure for reducing fractions
*/
void doReduceFraction( ) {
	Fraction frac;
	printf("Please enter a numerator: ");
	frac.numerator = getIntBounded(1, 10000, 1);
	printf("Please enter a denominator: ");
	frac.denominator = getIntBounded(1, 10000, 1);
	reduceFraction(&frac);
}

//void doComputeFN( ) {
//	printf_s("%s%s%s",
//			 "=================\n",
//			 "== COMPUTE F^N ==\n",
//			 "=================\n");
//
//	//	user creates matrices
//	printf("[ADJACENCY MATRIX]:\n");
//	Matrix * pMatrixA = userCreateMatrix( );
//
//	printf("Enter an integer greater than 0: ");
//	int power = getIntBounded(1, 15, 1);
//
//	for ( int i = 1; i < power; i++) {
//		printf("== F^%d ==\n", i);
//		multiplyMatrices2D(pMatrixA, pMatrixA);
//	}
//
//	//	de-allocate matrices
//	destroyMatrix2D(pMatrixA);
//
//	printf_s("%s",
//			 "(Returning to main menu...)\n");
//
//}

/*
procedure for adding fractions
*/
void doAddFractions( ) {

	Fraction fracA, fracB;

	printf("[FRACTION A]\n");
	printf("Please enter a numerator: ");
	fracA.numerator = getIntBounded(1, 10000, 1);
	printf("Please enter a denominator: ");
	fracA.denominator = getIntBounded(1, 10000, 1);
	printf("[FRACTION B]\n");
	printf("Please enter a numerator: ");
	fracB.numerator = getIntBounded(1, 10000, 1);
	printf("Please enter a denominator: ");
	fracB.denominator = getIntBounded(1, 10000, 1);

	Fraction fracC = fractionSum(fracA, fracB);

	printf("%d/%d + %d/%d = %d/%d.\n",
		   fracA.numerator, fracA.denominator,
		   fracB.numerator, fracB.denominator,
		   fracC.numerator, fracC.denominator);

	return;
}

/*
procedure for subtracting fractions
*/
void doSubFractions( ) {

	Fraction fracA, fracB;

	//	GET DATA
	printf("[FRACTION A]\n");
	printf("Please enter a numerator: ");
	fracA.numerator = getIntBounded(1, 10000, 1);
	printf("Please enter a denominator: ");
	fracA.denominator = getIntBounded(1, 10000, 1);
	printf("[FRACTION B]\n");
	printf("Please enter a numerator: ");
	fracB.numerator = getIntBounded(1, 10000, 1);
	printf("Please enter a denominator: ");
	fracB.denominator = getIntBounded(1, 10000, 1);

	//	DO CALCULATION
	Fraction fracC = fractionDifference(fracA, fracB);

	//	PRINT RESULTS
	printf("%d/%d - %d/%d = %d/%d.\n",
		   fracA.numerator, fracA.denominator,
		   fracB.numerator, fracB.denominator,
		   fracC.numerator, fracC.denominator);

	return;
}

/*
procedure for multiplying fractions
*/
void doMulFractions( ) {
	Fraction fracA, fracB;
	printf("[FRACTION A]\n");
	printf("Please enter a numerator: ");
	fracA.numerator = getIntBounded(1, 10000, 1);
	printf("Please enter a denominator: ");
	fracA.denominator = getIntBounded(1, 10000, 1);
	printf("[FRACTION B]\n");
	printf("Please enter a numerator: ");
	fracB.numerator = getIntBounded(1, 10000, 1);
	printf("Please enter a denominator: ");
	fracB.denominator = getIntBounded(1, 10000, 1);
	Fraction fracC = fractionProduct(fracA, fracB);

	//	PRINT RESULTS
	printf("%d/%d %c %d/%d = %d/%d.\n",
		   fracA.numerator, fracA.denominator, 158,
		   fracB.numerator, fracB.denominator,
		   fracC.numerator, fracC.denominator);
	return;
}

/*
procedure for dividing fractions
*/
void doDivFractions( ) {
	Fraction fracA, fracB;
	printf("[FRACTION A]\n");
	printf("Please enter a numerator: ");
	fracA.numerator = getIntBounded(1, 10000, 1);
	printf("Please enter a denominator: ");
	fracA.denominator = getIntBounded(1, 10000, 1);
	printf("[FRACTION B]\n");
	printf("Please enter a numerator: ");
	fracB.numerator = getIntBounded(1, 10000, 1);
	printf("Please enter a denominator: ");
	fracB.denominator = getIntBounded(1, 10000, 1);
	Fraction fracC = fractionQuotient(fracA, fracB);

	//	PRINT RESULTS
	printf("%d/%d %c %d/%d = %d/%d.\n",
		   fracA.numerator, fracA.denominator,
		   246, //	division sign
		   fracB.numerator, fracB.denominator,
		   fracC.numerator, fracC.denominator);
	return;
}


/*
reduce a fraction
@param *pFraction, pointer to the fraction
*/
int reduceFraction(Fraction * pFraction) {
	Fraction beforeFraction;
	beforeFraction.numerator = pFraction->numerator;
	beforeFraction.denominator = pFraction->denominator;
	int cf = 0;
	for ( int divisor = 1; divisor <= abs(pFraction->denominator) && divisor <= abs(pFraction->numerator); divisor++ ) {
		cf = 1; 
		while ( cf ) {
			pFraction->denominator /= cf;
			pFraction->numerator /= cf;
			cf = commonFactor(pFraction->denominator, pFraction->numerator);
		} 

		if ( pFraction->denominator < 0 ) {
			pFraction->denominator = -pFraction->denominator;
			pFraction->numerator *= -1;
		}

		//	PRINT RESULTS

				printf("%d/%d reduced to %d/%d.\n",
				beforeFraction.numerator,
				beforeFraction.denominator,
				pFraction->numerator,
				pFraction->denominator);

	
		return 0;
	}
}

/*
print a fraction
@param *pFraction, pointer to the fraction
*/
void printFraction(Fraction pFraction) {
	if ( abs(pFraction.denominator) == 1 ) {
		printf("%d", pFraction.numerator);
	} else {
		printf("%d/%d", pFraction.numerator, pFraction.denominator);
	}
}

/*
calculate the length in characters of a fraction
*/
int fractionLength(Fraction pFraction) {
	char numStr[100];
	if ( pFraction.denominator != 1 ) {
		sprintf_s(numStr, 100, "%d/%d", pFraction.numerator, pFraction.denominator);
	} else {
		sprintf_s(numStr, 100, "%d", pFraction.numerator);
	}
	return strlen(numStr);
}

/*
find and return the lowest common factor between two integers
@param n, the first integer
@param m, the second integer
*/
int commonFactor(int n, int d) {
	n = abs(n);
	d = abs(d);
	for ( int i = 2; i <= n && i <= d; i++ ) {
		if ( n%i == 0 && d%i == 0 ) {
			return i;
		}
	}
	return 0;
}

/*
calculate the sum of two fractions
@param	*fractionA, the first fraction
@param	*fractionB, the second fraction
*/
Fraction fractionSum(Fraction fractionA, Fraction fractionB) {
	Fraction sumFrac;
	sumFrac.denominator = fractionA.denominator*fractionB.denominator;
	sumFrac.numerator = fractionB.numerator*fractionA.denominator + fractionA.numerator*fractionB.denominator;
	reduceFraction(&sumFrac);
	return sumFrac;
}

/*
calculate the difference of two fractions
@param	*fractionA, the first fraction
@param	*fractionB, the second fraction
*/
Fraction fractionDifference(Fraction fractionA, Fraction fractionB) {
	Fraction difFrac;
	difFrac.denominator = fractionA.denominator*fractionB.denominator;
	difFrac.numerator = fractionA.numerator*fractionB.denominator - fractionB.numerator*fractionA.denominator;
	reduceFraction(&difFrac);
	return difFrac;
}

/*
calculate the product of two fractions
@param	*fractionA, the first fraction
@param	*fractionB, the second fraction
*/
Fraction fractionProduct(Fraction fractionA, Fraction fractionB) {
	Fraction prodFrac;
	prodFrac.denominator = fractionA.denominator*fractionB.denominator;
	prodFrac.numerator = fractionB.numerator*fractionA.numerator;
	reduceFraction(&prodFrac);
	return prodFrac;
}

/*
calculate the quotient of two fractions
@param	*fractionA, the first fraction
@param	*fractionB, the second fraction
*/
Fraction fractionQuotient(Fraction fractionA, Fraction fractionB) {
	Fraction quotFrac;
	quotFrac.denominator = fractionB.denominator*fractionA.numerator;
	quotFrac.numerator = fractionA.denominator*fractionB.numerator;
	reduceFraction(&quotFrac);
	return quotFrac;
}

/*
get the user's menu choice and validate input
*/
int getUserChoice (void) {
	int ret_choice;
	int valid_choice = 0;
	while ( !valid_choice ) {
		valid_choice = scanf_s("%d", &ret_choice);
		if ( !valid_choice ) {
			printf("Please enter an integer: ");
			clearKeyboardBuffer( );
		}
	}
	return ret_choice;
}

/*
procedure for multiplying two matrices
*/
void doMatrixMultiplication( ) {
	
	printf_s("%s%s%s",
			"===========================\n",
			"== MATRIX MULTIPLICATION ==\n",
			"===========================\n");

	//	user creates matrices
	printf("[MATRIX A]:\n");
	Matrix * pMatrixA = userCreateMatrix( );
	printf("[MATRIX B]:\n");
	Matrix * pMatrixB = userCreateMatrix( );
	multiplyMatrices2D(pMatrixA, pMatrixB);

	//	de-allocate matrices
	destroyMatrix2D(pMatrixA);
	destroyMatrix2D(pMatrixB);

	printf_s("%s",
			 "(Returning to main menu...)\n");
}

/*
procedure for summing two matrices
*/
void doMatrixAddition() {
	printf_s("%s%s%s",
			 "=====================\n",
			 "== MATRIX ADDITION ==\n",
			 "=====================\n");

	//	user creates matrices
	printf("[MATRIX A]:\n");
	Matrix * pMatrixA = userCreateMatrix( );
	printf("[MATRIX B]:\n");
	Matrix * pMatrixB = userCreateMatrix( );
	addMatrices2D(pMatrixA, pMatrixB, 0);

	//	de-allocate matrices
	destroyMatrix2D(pMatrixA);
	destroyMatrix2D(pMatrixB);

	printf_s("%s",
			 "(Returning to main menu...)\n");
}

/*
procedure for finding the difference between two matrices
*/
void doMatrixSubtraction( ) {
	printf_s("%s%s%s",
			 "========================\n",
			 "== MATRIX SUBTRACTION ==\n",
			 "========================\n");

	//	user creates matrices
	printf("[MATRIX A]:\n");
	Matrix * pMatrixA = userCreateMatrix( );
	printf("[MATRIX B]:\n");
	Matrix * pMatrixB = userCreateMatrix( );
	addMatrices2D(pMatrixA, pMatrixB, 1);

	//	de-allocate matrices
	destroyMatrix2D(pMatrixA);
	destroyMatrix2D(pMatrixB);

	printf_s("%s",
			 "(Returning to main menu...)\n");
}

/*
procedure for finding the determinant of a user-generated matrix
*/
void doFindDeterminant( ) {
	printf_s("%s%s%s",
			 "=============================\n",
			 "== FIND MATRIX DETERMINANT ==\n",
			 "=============================\n");

	//	user creates matrices
	printf("[MATRIX A]:\n");
	Matrix * pMatrixA = userCreateMatrix( );

	if ( pMatrixA ) {
		if ( pMatrixA->cols == pMatrixA->rows && pMatrixA->cols && pMatrixA->rows ) {
			printf("|A| is %d.\n",findDeterminant(pMatrixA));
		} else {
			printf("ERROR: Cannot find determinant of %dx%d matrix.\n", pMatrixA->rows, pMatrixA->cols);
		}
	}

	//	de-allocate matrices
	destroyMatrix2D(pMatrixA);

	printf_s("%s",
			 "(Returning to main menu...)\n");

}

/*
calculates the determinant of a nxn matrix
@param *pMatrix, pointer to matrix
*/
Fraction findDeterminant(Matrix * pMatrix) {
	int dimension = pMatrix->cols;
	assert(pMatrix->cols == pMatrix->rows);
	assert(pMatrix->cols);
	assert(pMatrix->rows);
	Fraction sum = makeFrac(0,1);
	Fraction subdeterminant = makeFrac(0,1);
	//	this is an nxn matrix and n > 0
	switch ( dimension ) {
	case 1:
		//return number in matrix;
		return pMatrix->matrix_data[ 0 ];
		break;
	case 2:
		//	return ad - bc;
		return fractionDifference(	//	ad - bc
			fractionProduct(pMatrix->matrix_data[ 0 ],pMatrix->matrix_data[ 3 ]),
			fractionProduct(pMatrix->matrix_data[ 1 ],pMatrix->matrix_data[ 2 ])
		);
		break;
	default:
		sum = makeFrac(0,1);
		Matrix * pSubmatrix = createMatrix2D(dimension - 1, dimension - 1);
		for ( int k = 0; k < dimension; k++ ) {
			setSubmatrixValues(k, pSubmatrix, pMatrix);	//	set values of submatrix according to value of k
			subdeterminant = fractionProduct(
				pMatrix->matrix_data[ k ],findDeterminant(pSubmatrix)
			);
			
			sum = fractionSum(sum, fractionProduct(subdeterminant, makeFrac((int)pow(-1, k), 1))); //	add or subtract this depending on k
		}
		destroyMatrix2D(pSubmatrix);
		return sum;
	}
}

/*
A submatrix has been created for the purpose of finding its determinant.
This function assigns values to all of the indices in that matrix so that
	the matrix determinant may be passed to the findDeterminant function.
*/
int setSubmatrixValues(int matrixIndex, Matrix * pSubmatrix, Matrix * pMatrix) {
	//	iterate through indices of submatrix to assign values
	//	pSubmatrix is nxn
	int iSubmatrix = 0;
	int iSourceMatrix = 0;
	int	skipRow = matrixIndex/pMatrix->cols;
	int skipColumn = matrixIndex%pMatrix->cols;
	for ( iSourceMatrix = 0; iSourceMatrix < pMatrix->cols*pMatrix->rows && iSubmatrix < pSubmatrix->cols*pSubmatrix->rows; iSourceMatrix++ ) {
		if ( skipRow == iSourceMatrix / pMatrix->cols || skipColumn == iSourceMatrix % pMatrix->cols ) {
			// do nothing
		} else {
			pSubmatrix->matrix_data[ iSubmatrix ] = pMatrix->matrix_data[ iSourceMatrix ];
			iSubmatrix++;
		}
	}
	return 0;
}

/*
procedure for calculating the inverse of a matrix
*/
void doFindInverse( ) {
	printf_s("%s%s%s",
			 "=========================\n",
			 "== FIND MATRIX INVERSE ==\n",
			 "=========================\n");

	//	user creates matrices
	printf("[MATRIX A]:\n");
	Matrix * pMatrixA = userCreateMatrix( );

	if ( pMatrixA ) {
		Fraction detA = findDeterminant(pMatrixA);
		if ( pMatrixA->cols == pMatrixA->rows && pMatrixA->cols && pMatrixA->rows ) {
			if ( detA.numerator != 0 && detA.denominator != 0 && pMatrixA->rows == 2) {
				Matrix * inverseMatrix = createMatrix2D(pMatrixA->rows, pMatrixA->cols);
				inverseMatrix->matrix_data[ 0 ] = fractionProduct(pMatrixA->matrix_data[ 3 ], makeFrac(1, detA.numerator));
				inverseMatrix->matrix_data[ 1 ] = fractionProduct(pMatrixA->matrix_data[ 1 ], makeFrac(-1, detA.numerator));
				inverseMatrix->matrix_data[ 2 ] = fractionProduct(pMatrixA->matrix_data[ 2 ], makeFrac(-1, detA.numerator));
				inverseMatrix->matrix_data[ 3 ] = fractionProduct(pMatrixA->matrix_data[ 0 ], makeFrac(1, detA.numerator));

				printf("[INVERSE OF MATRIX A]:\n");
				printMatrix(inverseMatrix);
				destroyMatrix2D(inverseMatrix);
			} else {
				printf("[INVERSE OF MATRIX A]: DNE OR CANNOT COMPUTE\n");
			}
		} else {
			printf("ERROR: Cannot find determinant of %dx%d matrix.\n", pMatrixA->rows, pMatrixA->cols);
		}
	}

	//	de-allocate matrix/ces
	destroyMatrix2D(pMatrixA);

	printf_s("%s",
			 "(Returning to main menu...)\n");
}

/*
called before program exits
*/
void doQuit( ) {
	//printf("doQuit was called\n");
}

/*
display an error message
*/
void doMenuErrorMessage( ) {
	//printf("doMenuErrorMessage was called\n");

}

/*
print the main menu
*/
void printMenu(void) {
	printf("Options:\n");
	for ( enum UserChoice i = UNDECIDED + 1; i < END; i++ ) {
		printf_s(" [%d] %s\n", i, menuOptionText[ i ]);
	}
}

/*
create a matrix with n rows and m columns
@param	n, the number of columns
@param	m, the number of rows
returns a pointer to the matrix
*/
Matrix * createMatrix2D(int n, int m) {
	Matrix * new_matrix = ( Matrix* ) malloc(sizeof(Matrix));
	new_matrix->rows = n;
	new_matrix->cols = m;
	Fraction * allocated_matrix = ( Fraction * ) malloc(sizeof(Fraction)*n*m);
	fillZero(allocated_matrix,n,m);
	new_matrix->matrix_data = allocated_matrix;
	//	printf_s("Matrix [%dx%d] created",n,m);
	//printMatrix(new_matrix);
	return new_matrix;
}

/*
negate all values in a matrix
@param *pMatrix, the matrix
*/
void negativeMatrix(Matrix * pMatrix) {
	for ( int i = 0; i < pMatrix->rows; i++ ) {
		for ( int j = 0; j < pMatrix->cols; j++ ) {
			pMatrix->matrix_data[ i*pMatrix->cols + j ] = fractionProduct(pMatrix->matrix_data[ i*pMatrix->cols + j ],makeFrac( -1,1));
		}
	}
}


/*
calculate and print the matrix sum of two matrices
@param *pMatrixA, the first matrix
@param *pMatrixB, the second matrix
*/
void addMatrices2D(Matrix * pMatrixA, Matrix * pMatrixB, int doSubtract) {
	int a_rows = pMatrixA->rows;
	int a_cols = pMatrixA->cols;
	int b_rows = pMatrixB->rows;
	int b_cols = pMatrixB->cols;
	if ( doSubtract ) {
		negativeMatrix(pMatrixB);
	}
	if ( a_cols != b_cols || a_rows != b_rows ) {
		printf("Cannot add %dx%d matrix to %dx%d matrix.", pMatrixA->rows, pMatrixA->cols, pMatrixB->rows, pMatrixB->cols);
		return;
	}
	Matrix * pSumMatrix = createMatrix2D(a_rows, a_cols);
	int	matrixIndex;
	for ( int i = 0; i < a_rows; i++ ) {
		for ( int j = 0; j < b_cols; j++ ) {
			//	calculate the value for each spot in the matrix
			matrixIndex = i * b_cols + j; //	find the index to update
			pSumMatrix->matrix_data[ matrixIndex ] = fractionSum(pMatrixA->matrix_data[ matrixIndex ],pMatrixB->matrix_data[ matrixIndex ]);
		}
	}
	if ( doSubtract ) {
		printf("Matrix difference:\n");
	} else {
		printf("Matrix sum:\n");
	}
	printMatrix(pSumMatrix);
	destroyMatrix2D(pSumMatrix);
	return;
}

/*
calculate and print the matrix product of two matrices
@param *pMatrixA, the first matrix
@param *pMatrixB, the second matrix
*/
void multiplyMatrices2D(Matrix * pMatrixA, Matrix * pMatrixB) {
	int a_rows = pMatrixA->rows;
	int a_cols = pMatrixA->cols;
	int b_rows = pMatrixB->rows;
	int b_cols = pMatrixB->cols;
	if ( a_cols != b_rows ) {
		printf("Cannot multiply %dx%d matrix by %dx%d matrix.", pMatrixA->rows, pMatrixA->cols, pMatrixB->rows, pMatrixB->cols);
		return;
	}
	Matrix * pProductMatrix = createMatrix2D(a_rows, b_cols);
	Fraction	sum = makeFrac(0, 1);
	int	pProductMatrixIndex;
	Fraction factorA, factorB;
	for ( int i = 0; i < a_rows; i++ ) {
		for ( int j = 0; j < b_cols; j++ ) {
			//	calculate the value for each spot in the matrix
			pProductMatrixIndex = i * b_cols + j; //	find the index to update
			sum = makeFrac(0,1);
			for ( int k = 0; k < a_cols; k++ ) {
				//	increment sum by products of matrix pairs
				factorA = pMatrixA->matrix_data[ i*a_cols + k ];
				factorB = pMatrixB->matrix_data[ k*b_cols + j ];
				sum = fractionSum(sum,fractionProduct(factorA,factorB));
			}
			pProductMatrix->matrix_data[ pProductMatrixIndex ] = sum;
		}
	}

	//	PRINT RESULTS
	printf("Matrix product:\n");
	printMatrix(pProductMatrix);
	destroyMatrix2D(pProductMatrix);
	return;
}

/*
calculate the product for one cell of a product matrix
@param *pMatrixA, the first matrix
@param *pMatrixB, the second matrix
@param row, the row of the cell in the product matrix
@param col, the column of the cell in the product matrix
*/
Fraction matrixCellProduct(Matrix * pMatrixA, Matrix * pMatrixB, int row, int col) {
	Fraction sum = makeFrac(0,1);
	int per_row = pMatrixA->rows;
	int per_col = pMatrixB->cols;
	for ( int i = 0; i < pMatrixA->rows; i++ ) {
		sum = fractionSum(sum,fractionProduct(pMatrixA->matrix_data[ row*per_col + i ],pMatrixB->matrix_data[ col + i * per_row ]));
	}
	return sum;
}

/*
count the digits of a number
@param _number, integer
*/
int countDigits(int _integer) {
	int places=1;
	while ( _integer ) {
		_integer /= 10;
		places++;
	}
	return places;
}

/*
count the digits of a number
@param _number, a double
*/
int countDigitsf(double _number) {
	char str[5];
	_gcvt_s(str, 5, _number, 4);
	return strlen(str);
}

/*
determine the highest number of digits of all values in a matrix
@param *pMatrix, a pointer to the matrix
*/
int getMostDigits(Matrix * pMatrix) {
	int highest = 0;
	int digits = 0;
	for ( int i = 0; i < pMatrix->rows*pMatrix->cols; i++ ) {
		digits = fractionLength(pMatrix->matrix_data[ i ]);
		if ( highest < digits ) {
			highest = digits;
		}
	}
	return highest;
}

/*
procedure for creating a matrix based on user parameters
returns a pointer to the created matrix
*/
Matrix * userCreateMatrix( ) {

	printf_s("Enter the number of rows n: ");
	int user_rows = getIntBounded(1, 10, 1);
	printf_s("Enter the number of columns m: ");
	int user_columns = getIntBounded(1, 10, 1);

	Matrix * pMatrix = createMatrix2D(user_rows, user_columns);

	printf("Do you want to fill the matrix now (f) or leave it full of zeroes (z)? ");

	char ch;
	int valid_input = 0;
	while ( !valid_input ) {
		valid_input = scanf_s("%c", &ch);
		if ( !valid_input ) {
			printf("Invalid response. ");
			clearKeyboardBuffer( );
		} else {
			switch ( ch ) {
			case 'F':
			case 'f':
				userFillMatrix(pMatrix);
				break;
			case 'z':
			case 'Z':
			default:
				//	do nothing
				break;
			}
		}
	}

	return pMatrix;
}

/*
have the user input numerical values for the matrix
@param	*pMatrix, pointer to matrix
returns a pointer to the matrix filled
*/
Matrix * userFillMatrix(Matrix * pMatrix) {
	printf("userFillMatrix was called.\n");
	int rows = pMatrix->rows;
	int cols = pMatrix->cols;
	char chbuf = 'a';
	int numbuf=0;
	int denbuf=1;
	int valid_numerator = 0;
	int valid_denominator = 0;

	enum FractionParseState fps = BETWEEN_FRACTIONS;

	for ( int counter = 0; counter < rows*cols; ) {

		valid_numerator = 0;

		while ( !valid_numerator ) {
			valid_numerator = scanf_s("%d", &numbuf);
		}

		while ( chbuf != '/' && chbuf != ' ' && chbuf != '\n' ) {
			scanf_s("%c", &chbuf);
		}

		switch ( chbuf ) {
		case '/':
		default:
			valid_denominator = 0;
			while ( !valid_denominator ) {
				valid_denominator = scanf_s("%d", &denbuf);
			}
		case ' ':
		case '\n':
			if ( !denbuf )
				denbuf = 1;
			pMatrix->matrix_data[ counter ].numerator = numbuf;
			pMatrix->matrix_data[ counter ].denominator = denbuf;
			numbuf = 0;
			denbuf = 1;
			chbuf = 0;
			counter++;
			break;
		}
	}

	/*
	int counter = 0;
	double dBuffer = 0;
	int valid_input = 0;
	printf("Please enter values for the matrix separated by spaces: ");
	while ( counter < rows*cols ) {
		valid_input = scanf_s("%lf", &dBuffer);
		if ( valid_input ) {
			pMatrix->matrix_data[ counter ] = dBuffer;
			counter++;
		} else {
			valid_input = 0;
			clearKeyboardBuffer( );
		}
	}
	*/

	clearKeyboardBuffer( );
	
	printf("User created matrix:");
	printMatrix(pMatrix);
	return pMatrix;
}

/*
clearKeyboardBuffer
pre-condition:	None
post-condition:	The keyboard buffer has been cleared.
*/
void clearKeyboardBuffer(void) {
	char ch = 'a';
	while ( ch != '\n' ) {
		scanf_s("%c", &ch);
	}
}

/*
get an integer from the user within certain bounds
@param lower_bound
the lowest acceptable integer
@param upper_bound
the highest acceptable integer
@param inclusive
true or false, whether the endpoints are themselves acceptable
*/
int getIntBounded(int lower_bound, int upper_bound, int inclusive) {
	int valid_input = 0;
	int user_generated_integer;
	while ( !valid_input ) {
		valid_input = scanf_s("%d", &user_generated_integer);
		if ( !valid_input ) {
			clearKeyboardBuffer( );
			printf("Sorry, that's not a valid input. Try again: ");
		} else {
			if ( user_generated_integer > upper_bound || user_generated_integer < lower_bound ) {
				if ( inclusive ) {
					printf("Sorry, that's out of bounds [%d-%d].", lower_bound, upper_bound);
				} else {
					printf("Sorry, that's out of bounds (%d-%d).", lower_bound, upper_bound);
				}
				valid_input = 0;
			}
		}
	}
	clearKeyboardBuffer( );
	return user_generated_integer;
}

/*
print the contents of a matrix
@param	*pMatrix, pointer to matrix
*/
void printMatrix(Matrix * pMatrix) {
	if ( !pMatrix ) {
		printf("Cannot print NULL matrix.");
		return;
	}
	if ( pMatrix->cols < 1 || pMatrix->rows < 1 ) {
		printf("Matrix does not meet minimum dimensions.");
		return;
	}

	//int width = getMostDigits(pMatrix)+1;
	int width = getMostDigits(pMatrix)+2;

	int rows = pMatrix->rows;
	int cols = pMatrix->cols;

	//	print top corners
	printf("\n%c", 218);

	for ( int i = 0; i < cols; i++ ) {
		printf("%*s", width, "");
	}

	printf("%*s%c",width-1,"", 191);

	for ( int i = 0; i < rows*cols; i++ ) {
		int fraclength = fractionLength(pMatrix->matrix_data[ i ]);
		if ( i%cols == 0 ) {
			if ( i > cols-1 ) {
				printf("%*s%c",width-1,"", 179);
			}
			printf("\n%c", 179);
		}
		printf("%*s", width - fraclength,"" ); // fix this
		printFraction(pMatrix->matrix_data[ i ]);

	}

	//	print bottom corners
	printf("%*s%c\n%c", width-1,"", 179, 192);
	for ( int i = 0; i < cols; i++ ) {
		printf("%*s", width, "");
	}
	printf("%*s%c\n",width-1,"", 217);

	return;
}

/*
deallocate a matrix
@param	*pMatrix, pointer to matrix
*/
void destroyMatrix2D(Matrix * pMatrix) {
	free(pMatrix->matrix_data);
	free(pMatrix);
	//	printf_s("Matrix destroyed.\n");
}

/*
fill an array with zeroes
@param	*fArray, the rational array
@param	n, array rows
@param	m, array columns (false indexing)
*/
double * fillZero(Fraction * fArray, int n, int m) {
	for ( int i = 0; i < n*m; i++) {
		fArray[ i ].denominator = 1;
		fArray[ i ].numerator = 0;
	}
	return fArray;
}
