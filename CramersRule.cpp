#include<iostream>
#include<cmath>
int getMatrixElimination(double ** matrix,int i,int j,int rows,int columns);
int getDeterminant(double ** matrix,int rows,int columns){
if(rows==2 && columns==2){
    return (matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0]);
}
int sum=0;
for(int i=0;i<columns;i++){
   sum+=pow(-1,i)*matrix[0][i]*getMatrixElimination(matrix,0,i,rows,columns);
}
return sum;
}
int getMatrixElimination(double ** matrix,int rowEliminate,int columnEliminate,int rows,int columns){
    double **newMatrix=new double*[rows-1];
    for(int i=0;i<rows-1;i++){
        newMatrix[i]=new double[columns-1];
    }
    int newI=0;
    int newJ=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
          if(i!=rowEliminate && j!=columnEliminate){
            newMatrix[newI][newJ]=matrix[i][j];
            newJ++;
            if(newJ==columns-1){
                newJ=0;
                newI++;
            }
          }
        }
    }
    return getDeterminant(newMatrix,rows-1,columns-1);
};
double ** substitude(double** A,int x,int rows,int columns,double* B){
double** Ai=new double*[rows];
for(int i=0;i<rows;i++){
    Ai[i]=new double[columns];
}
for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
        Ai[i][j]=A[i][j];
    }
}
for(int i=0;i<rows;i++){
    Ai[i][x]=B[i];
}
return Ai;
}
// the answers of xi is saved into 1D array that returned by function
//Xi=|Ai|/|A|
double * solveLinearSystemEquationsUsingCramersRule(double **A,double *B,
int rowsOfA,int columnsOfA){
    if(getDeterminant(A,rowsOfA,columnsOfA)==0){
        throw "this system doesnt have an answer or have an infinity naswers";
    }
    double* answers=new double[columnsOfA];

for(int i=0;i<columnsOfA;i++){
    double **Ai=substitude(A,i,rowsOfA,columnsOfA,B);
    answers[i]=getDeterminant(Ai,rowsOfA,columnsOfA)/
    getDeterminant(A,rowsOfA,columnsOfA);
}
return answers;
}
int main(int length,char* args[]){
double** A=new double*[3]{new double[3]{5,-3,-10},
                         new double[3]{2,2,-3},
                         new double[3]{-3,-1,5}};
double * B=new double[3]{-9,4,-1};
double *answers=solveLinearSystemEquationsUsingCramersRule(A,B,3,3);
for(int i=0;i<3;i++){
    std::cout<<"x"<<i<<"="<<answers[i]<<"\t";
}
}