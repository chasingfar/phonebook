#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    if(argc<2){
        printf("ERROR: no input file\n");
        exit(0);
    }

    FILE *fp;
    FILE *output = fopen("output.txt", "w");
    double sum_a[argc],sum_f[argc], tmp_a, tmp_f;
    int i,j;
    char append[50], find[50], input_file_name[50];

    for(j=1;j<argc;j++){
        sprintf(input_file_name,"%s.txt",argv[j]);
        fp = fopen(input_file_name, "r");
        if (!fp) {
            printf("ERROR opening input file %s\n",input_file_name);
            exit(0);
        }
        sum_a[j]=0.0;
        sum_f[j]=0.0;
        for (i = 0; i < 100; i++) {
            if (feof(fp)) {
                printf("ERROR: You need 100 datum instead of %d\n", i);
                printf("run 'make run' longer to get enough information\n\n");
                exit(0);
            }
            fscanf(fp, "%s %s %lf %lf\n", append, find, &tmp_a, &tmp_f);
            sum_a[j] += tmp_a;
            sum_f[j] += tmp_f;
        }
        fclose(fp);
    }


    fprintf(output, "append()");
    for(j=1;j<argc;j++) {
        fprintf(output, " %lf",sum_a[j]/100.0);
    }
    fprintf(output, "\nfindName()");
    for(j=1;j<argc;j++) {
        fprintf(output, " %lf",sum_f[j]/100.0);
    }

    fclose(output);
    return 0;
}
