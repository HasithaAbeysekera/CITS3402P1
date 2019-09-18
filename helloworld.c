#include <stdio.h>
#include <time.h>
#include <omp.h>

int main()
{

   clock_t begin, end;

   long int numSteps = 1000000;
   double step;

   int i;
   double x, pi, sum = 0.0;

   step = 1 / (double)numSteps;

   begin = clock();

   omp_set_num_threads(4); //I have set the number of threads =4, you can change this.
#pragma omp parallel
   {
      for (i = 0; i < numSteps; i++)
      {
         x = (i + 0.5) * step;
         sum += 4.0 / (1.0 + x * x);
      }
      pi = sum * step;
      end = clock();
      printf("pi=%18.16f and time =%f\n", pi, (double)(end - begin) / CLOCKS_PER_SEC);
   }
}