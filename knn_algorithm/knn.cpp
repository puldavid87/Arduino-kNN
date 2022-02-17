/**********************************************
   ***************LIBRARIES*****************
 ********************************************/

#include <Arduino.h>
#include <avr/pgmspace.h>
#include "ListLib.h"

/******************************************
 *************** DEFINITIONS ************* 
 *****************************************/
#define cols 5
#define rows 120
#define labels 3

/**************************************
 **********GLOBAL VARIABLE ***********
 *************************************/
uint8_t split;
List <int> test_set; //creates the new vector 
extern float training_set[rows][cols];
uint8_t random_test (uint8_t test, uint8_t lim);
void array_test_set ();
uint8_t classifier (uint8_t k, float *input);

/*
 * Dividing the dataset in training and test set with the input parameter as the percent value to assign to the test set
 */
void split_set (float value){
  // local variables
  uint8_t i=0,l=0,aux;
  // Getting the exact number to asign to the training and test set
  split=round(rows*value);
  randomSeed(39); 
  // randomly selection to add in test set vector
  test_set.Insert(0,0);
  for(i=0;i<split;i++){
        aux=random_test(random(1,rows-1),list.Count());
        test_set.Insert(i,aux);
    }
Serial.println("Done..!");     
}

/*
 * Subroutine to avoid storing the same random value
 */
uint8_t random_test (uint8_t test, uint8_t lim){
  uint8_t j=0,k=0;
  for(j=0;j<lim;j++){
    if(test!=test_set[j])
       k++;
    }
   if(k==test_set.Count())
      return test;
   else
       random_test(random(1,rows-1),test_set.Count());
  k=0;  
}
/*
 * Classifier routine
 */
uint8_t classifier (uint8_t k, float *input){
  uint8_t col;
  uint8_t fil;
  uint8_t i=0;
  uint8_t j, rep=0;
  uint8_t label;
  float aux;
  float aux_label;
  float sum=0; // sumatoria de la elevación al cuadrado de cada col
  float distance=0; // raiz de sumatoria
  uint8_t var;

  /*k neighboors matrix 
  |1|2|3| -> number of neighboors
  |2|1|1| -> label of the neighboor
  |0.1|0.2|0.3| -> distance
  */
 float matrix_k [3][k];
  /* labels
  |1|2|3| -> put the labels into a matrix
  |2|1|0| -> at the end ww storage the number of labels of each label
   */
 int matrix_labels[2][labels];

  // fill in with zeros

   for(;i<k;i++){
      matrix_k[0][i]=i+1.0;
      matrix_k[1][i]=0;
      matrix_k[2][i]=3000.0+i; // add highest distance
    /*
     |1|2|3|
     |0|0|0|
     |3000|3001|3002|
     */

     
    }
   // fill in with labels
   for(i=0;i<labels;i++){
    matrix_labels[0][i]=i+1;
    matrix_labels[1][i]=0;
    /*
     |1|2|3| 
     |0|0|0|
     */
    }
// k cycle
for(;rep<k;rep++){
   for(fil=0;fil<rows;fil++){
       for(i=0;i<split;i++){
            if(fil==test_set[i])
              var=test_set[i];
          }
      if(fil==var)
        continue;
      else{      
           for(col=0;col<cols-1;col++){ // -1 col for the label
              sum=sum+pow(training_set[fil][col]-input[col],2);
             }
            distance=sqrt(sum);
            if(distance<matrix_k[2][k-1]){
                 matrix_k[2][k-1]=distance;
                 matrix_k[1][k-1]=training_set[fil][cols-1];
                 //sort by greater distance
                 for (i=0;i<k;i++){
                     for(j=i+1;j<k;j++){
                          if(matrix_k[2][i]>matrix_k[2][j]){
                            //distancia
                             aux=matrix_k[2][i];
                             matrix_k[2][i]=matrix_k[2][j];
                             matrix_k[2][j]=aux;
                             // etiqueta
                              aux_label=matrix_k[1][i];
                             matrix_k[1][i]=matrix_k[1][j];
                             matrix_k[1][j]=aux_label;
                            } //end if
                      } //end for
                  }
                 //end sort
              } 
              sum=0; //restart sum
     }
   }
}   
        // count labels for k neighboors
        for(i=0;i<labels;i++){
          for(j=0;j<k;j++){
              if(matrix_labels[0][i]==matrix_k[1][j]){
                 matrix_labels[1][i]++;
                }
            }
          }
         // looking for the highest number of labels
        label=(int)matrix_labels[0][0];
        aux=(int)matrix_labels[1][0];
        for(i=1;i<labels;i++){
            if(matrix_labels[1][i]>aux)
               label=(int)matrix_labels[0][i];
          }      
    return label;    
 }

/*
 * ACCURANCY: Once the model is made, we can determine the accurancy
 */
float accurancy_knn (uint8_t k){
  uint8_t i=0,j=0,out=0,accurancy=0;
  float accu;
  float vector[cols];
  for(;i<split;i++){
    for(j=0;j<cols;j++){
      vector[j]=training_set[list[i]][j];
      }
    out=classifier(k,&vector[0]);
    if(out==(int)training_set[test_set[i]][cols-1]){
      accurancy++;
      }
    } 
    accu=(float)(accurancy/(float)(split));
    Serial.println(String("Acc:")+String(accu));
  return (accu);
 }

     
