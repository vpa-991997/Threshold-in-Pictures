//Phuong Anh Vu
//CAP 4453 Spring 2020
//Week 1 Assignment 
#include <stdio.h>                          /* Sobel.c */
#include <math.h>

        int pic[256][256];
        int outpicx[256][256];
        int outpicy[256][256];
        int maskx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
        int masky[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
        double ival[256][256],maxival;

int main(argc,argv)
int argc;
char **argv;
{
        int i,j,p,q,mr,sum1,sum2;
        double lowthreshold, highthreshold;
        FILE *fo1, *fo2, *fo3, *fp1, *fopen();
        
        fp1 = fopen ("face05.pgm", "rb"); //Read input
        // Write ouput
		    fo1 = fopen ("MagnitudeHW1.pgm", "wb");
        fo2 = fopen ("LowThreshold.pgm", "wb");
        fo3 = fopen ("HighThreshold.pgm", "wb");
        
        //Add header line .pgm
		//Set rol and col to be 256
        fprintf (fo1, "P5\n");
        fprintf (fo1, "256 256\n");
        fprintf (fo1, "255\n");
        
        fprintf (fo2, "P5\n");
        fprintf (fo2, "256 256\n");
        fprintf (fo2, "255\n");
        
        fprintf (fo3, "P5\n");
        fprintf (fo3, "256 256\n");
        fprintf (fo3, "255\n");
        
		for (i= 0; i<15; i++){
          getc (fp1);
    }

        for (i=0;i<256;i++)
        { for (j=0;j<256;j++)
                {
                  pic[i][j]  =  getc (fp1);
                }
        }

        mr = 1;
        for (i=mr;i<256-mr;i++)
        { for (j=mr;j<256-mr;j++)
          {
             sum1 = 0;
             sum2 = 0;
             for (p=-mr;p<=mr;p++)
             {
                for (q=-mr;q<=mr;q++)
                {
                   sum1 += pic[i+p][j+q] * maskx[p+mr][q+mr];
                   sum2 += pic[i+p][j+q] * masky[p+mr][q+mr];
                }
             }
             outpicx[i][j] = sum1;
             outpicy[i][j] = sum2;
          }
        }

        maxival = 0;
        for (i=mr;i<256-mr;i++)
        { for (j=mr;j<256-mr;j++)
          {
             ival[i][j]=sqrt((double)((outpicx[i][j]*outpicx[i][j]) +
                                      (outpicy[i][j]*outpicy[i][j])));
             if (ival[i][j] > maxival)
                maxival = ival[i][j];

           }
        }



        for (i=0;i<256;i++)
          { for (j=0;j<256;j++)
            {
             ival[i][j] = (ival[i][j] / maxival) * 255;            
             fprintf(fo1,"%c",(char)((int)(ival[i][j])));
             
            }
          }
          for (i=0;i<256; i++)
          {
          	for (j=0; j <256; j++)
          	{
        // Low Threshold chose Low Threshold =35
          		if (ival[i][j] > 35)
          		fprintf ( fo2, "%c", (char)((int)(255)));
        		else
          		fprintf(fo2, "%c", (char)((int)(0)));
			 	// High threshold chose High Threshold = 65
			 	if (ival[i][j] > 65)
			 	fprintf(fo3, "%c", (char)((int)(255)));
			 	else
			 	fprintf (fo3, "%c", (char)((int)(0)));
			  }  
		  }  
		  fclose (fp1);
		  fclose (fo1);
		  fclose (fo2);
		  fclose (fo3);
		  return 0;
		  
}
