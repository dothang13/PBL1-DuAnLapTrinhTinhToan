#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

const long long MAX = 100;
const float TOLERANCE = 0.0001;
typedef float MT[MAX][MAX + 1];
#define newline printf("\n\n")

FILE *f, *fw;
char nf[100];

int check_input_file(int kt);

int check_error(int d);

void read_file_matrix(char nf[100], FILE **f);

int read_matrix_from_file(FILE *f, int *n, MT a);

void read_matrix_from_keyboard(int n, MT a);

void Print(int n, MT a, int c);

void Print_file(FILE *f, int n, MT a); // xuat ra file

void copy(int n, MT a, MT A);

void find_mt(MT a, MT b, int n, int c);

void swap(int p, int q, MT a, int n);

void upper_triangle_maxtrix(int n, MT a, float *dt, int pr);

int solve_Cramer(MT a, int n, float x[]);

void show_value(int n, float a[]);

void show_value_file(FILE *f, int n, float a[]);

void find_value(int n, MT a, float x[]);

void write_file();

float value(float x);

void rank(MT a, int n, int *rA, int *rA2);

void setcolor(int backgound_color, int text_color);

void infor();

void menu();

int main() {
    infor();
    int n, i, j, opt, temp, err;
    char input[100];
    MT B, A; // MT B: ma tran ban dau => A de xu li;
    float x[MAX];
    float *dt;
    int kt = 0;// nhap file chua? => neu chua chay file default
    int kt_opt;
    int rA, rA2;
    FILE *fres;
    fres = fopen("KETQUA.TXT", "w"); // reset du lieu tu dau
    
    another:
    menu();
    newline;
	kt_opt= 0;
	err = 0;
	while (kt_opt==0) // kiem tra opt nha co hop le ko
	{
	    printf("Moi ban nhap yeu cau: ");
	    fgets(input, sizeof(input), stdin);
	    input[strcspn(input, "\n")] = 0;
	    if ((strlen(input)==1) && (input[0]>='1') && (input[0]<='6'))
	    	{
	    		opt = atoi(input);
	    		break;
			}
		err++;
		if (check_error(err)) exit(0);
		printf("Yeu cau cua ban khong hop le. Vui long nhap lai!!\n\n");
		
 	}
    newline;
	
    switch (opt) {
        case 1: // mo file (nhap du lieu)
        	err = 0;
	        read_again:
	            read_file_matrix(nf, &f);
	            if (!read_matrix_from_file(f, &n, B)) {
	                err++;
	                if (err==3) printf("\n");
	                if (check_error(err)) exit(0);
	                printf(" Vui long nhap lai!\n\n");
	                goto read_again;
	                setcolor(0, 12);
	                setcolor(0, 15);
	                goto carryon;
	            }
	            kt = 1;
	            printf("He phuong trinh vua nhap la: \n\n");
	            Print(n, B, 0);
	
	            fprintf(fres, "HE PHUONG TRINH: \n\n");
	            Print_file(fres, n, B);
	
	
	        carryon:
	        	setcolor(0,7);
	            printf("\nNhan enter de tiep tuc...");
	            setcolor(0,15);
	            getchar();
	            system("cls");
	            goto another;
            
		case 2: // nhap tu ban phim
			kt = 1;
			printf("Moi nhap cap cua ma tran: ");
			scanf("%d",&n);
			newline;
			read_matrix_from_keyboard(n,B);
			
			fprintf(fres, "HE PHUONG TRINH: \n\n");
            Print_file(fres, n, B);
            
            goto carryon;

        case 3: // Cramer
            if (!check_input_file(kt)) // chua co du lieu file thi chay file default
            {
            	printf("He phuong trinh (lay du lieu tu file DEFAULT.INP) \n");
            	f = fopen("DEFAULT.INP", "r");
		        if (f == NULL) {
		            printf("Khong the mo file DEFAULT.INP!\n");
		            goto carryon;
		        }
		        temp = read_matrix_from_file(f, &n, B);
		        fclose(f);
			}
            copy(n, A, B);
            setcolor(0, 11);
            printf("HE PHUONG TRINH BAN DAU LA:\n\n");
            setcolor(0, 15);
            Print(n, A, 0);
            setcolor(0, 11);
            printf("\nDAY LA CACH GIAI HE PHUONG TRINH TREN BANG PHUONG PHAP CRAMER:\n\n");
            setcolor(0, 15);
            temp = solve_Cramer(A, n, x);
            if (temp == 1) show_value(n, x);
            else 
			{
				setcolor(0,12);
				printf("He phuong trinh tren khong the giai bang phuong phap Cramer!!! (Det = 0)\n\n");
				setcolor(0,15);
			}
				
            fprintf(fres, "\nGiai he phuong trinh tren bang phuong phap CRAMER:\n\n");
            if (temp == 1) show_value_file(fres, n, x);
            else fprintf(fres, "He phuong trinh tren khong the giai bang phuong phap Cramer!!! (Det = 0)\n\n\n");

            goto carryon;

        case 4: //  Gauss
            if (!check_input_file(kt)) // chua co du lieu file thi chay file default
            {
            	printf("He phuong trinh (lay du lieu tu file DEFAULT.INP)\n");
            	f = fopen("DEFAULT.INP", "r");
		        if (f == NULL) {
		            printf("Khong the mo file DEFAULT.INP!\n");
		            goto carryon;
		        }
		        temp = read_matrix_from_file(f, &n, B);
		        fclose(f);
			}
            copy(n, A, B);
            setcolor(0, 11);
            printf("HE PHUONG TRINH BAN DAU LA:\n\n");
            setcolor(0, 15);
            Print(n, A, 0);
            setcolor(0, 11);
            printf("DAY LA CACH GIAI HE PHUONG TRINH TREN BANG PHUONG PHAP GAUSS:\n\n");
            setcolor(0, 15);
            fprintf(fres, "Giai he phuong trinh tren bang phuong phap GAUSS:\n");
			setcolor(0, 14);
            printf("\nBUOC 1: BIEN DOI MA TRAN TREN THANH MA TRAN TAM GIAC TREN\n\n\n");
            setcolor(0, 15);
            upper_triangle_maxtrix(n, A, dt, 1);
            rA = n;
            rA2 = n;
            rank(A, n, &rA, &rA2);
            if (rA == rA2)
			{
                if (rA == n) 
				{
                	setcolor(0, 12);
                    printf("\n     => HE PHUONG TRINH CO 1 NGHIEM DUY NHAT\n\n");
                    setcolor(0, 15);
                    fprintf(fres, "\n     => HE PHUONG TRINH CO 1 NGHIEM DUY NHAT\n\n");
                } 
				else 
				{
                	setcolor(0, 12);
                    printf("\n     => HE PHUONG TRINH CO VO SO NGHIEM\n\n");
                    setcolor(0, 15);
                    fprintf(fres, "\n     => HE PHUONG TRINH CO VO SO NGHIEM\n\n");
                    fprintf(fres, "--------------------------------------------\n\n");
                    goto carryon;
                }
            } 
			else
			{
            	setcolor(0, 12);
                printf("\n     => HE PHUONG TRINH VO NGHIEM\n\n");
                setcolor(0, 15);
                fprintf(fres, "\n     => HE PHUONG TRINH VO NGHIEM\n\n");
                fprintf(fres, "--------------------------------------------\n\n");
                goto carryon;
            }
			
			setcolor(0, 14);
            printf("\nBUOC 2: TIM NGHIEM\n\n\n");
            setcolor(0, 15);
            find_value(n, A, x);
            show_value(n, x);
            show_value_file(fres, n, x);
            fprintf(fres, "--------------------------------------------\n\n");
            goto carryon;

        case 5: // xuat nghiem ra file
            fclose(fres);
            write_file();
            fres = fopen("KETQUA.TXT", "w"); // reset du lieu tu dau
            goto carryon;

        case 6: // exit program
        	setcolor(0, 10);
            printf("CHUONG TRINH KET THUC !!\n");
            setcolor(0, 15);
            break;

        default:
            err++;
            if (check_error(err)) exit(0);
            setcolor(0, 12);
            printf("Yeu cau nhap vao khong ton tai, vui long nhap lai!!\n");
            setcolor(0, 15);
            goto carryon;
    }

    return 0;
}

void setcolor(int backgound_color, int text_color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

//Ham gioi thieu
void infor()
{
    int i;
    setcolor(0, 11);
    printf("\n%9c", 201);
    for (i = 0; i <= 100; i++) printf("%c", 205);
    printf("%c", 187);
    printf("\n        %c %100c", 4, 4);
    printf("\n        %c%101c%c", 4, ' ', 4);
    printf("\n        %c                                    DO AN LAP TRINH TINH TOAN                                %c",
           4, 4);
    printf("\n        %c%101c%c", 4, ' ', 4);
    printf("\n        %c        DE TAI: GIAI HE PHUONG TRINH DAI SO TUYEN TINH BANG PHUONG PHAP CRAMER, PHUONG PHAP GAUSS       %c",
           4, 4);
    printf("\n        %c%101c%c", 4, ' ', 4);
    printf("\n        %c%101c%c", 4, ' ', 4);
    printf("\n        %c            Sinh vien thuc hien:                          Giao vien huong dan:                %c",
           4, 4);
    printf("\n        %c            %c Nguyen Do Thang                              Do Thi Tuyet Hoa                 ",
           4, 45, 45, 4);
    printf("\n        %c            %c Huynh Bao Quyen  %60c", 4, 45, 4);
    printf("\n        %c%101c%c", 4, ' ', 4);
    printf("\n        %c", 200);
    for (i = 0; i <= 100; i++) printf("%c", 205);
    printf("%c\n", 188);
}

void menu() {
    setcolor(0, 14);
    printf("\n                                        %c   CAC CHUC NANG CUA CHUONG TRINH!   %c\n", 16, 17);
    printf("\n                          1. Nhap du lieu n va ma tran A tu file *.INP \n");
    printf("\n                          2. Nhap du lieu n va ma tran A tu ban phim \n");
    printf("\n                          3. Giai he phuong trinh dai so tuyen tinh bang phuong phap Cramer \n");
    printf("\n                          4. Giai he phuong trinh dai so tuyen tinh bang phuong phap Gauss \n");
    printf("\n                          5. Nhap ten file *.OUT luu du lieu dau ra \n");
    printf("\n                          6. Thoat chuong trinh \n");
    printf("\n                                                    -------\n");
    setcolor(0, 15);
}


int check_input_file(int kt)
{
    if (!kt) return 0;
    return 1;
}


int check_error(int d)
{
    if (d == 3)
	{
    	setcolor(0, 12);
        printf("BAN DA NHAP SAI 3 LAN LIEN TIEP. CHUONG TRINH KET THUC TAI DAY!!!\n");
        setcolor(0, 15);
        return 1;
    }
	else return 0;
}

void read_file_matrix(char nf[100], FILE **f)
{ // Doc ma tran, kiem tra ma tran co hop le hay khong
    int valid = 0;
    int count_error = 0;
    while (!valid)
	{
        printf("Moi nhap ten file: ");
        fgets(nf, MAX, stdin);
        nf[strcspn(nf, "\n")] = '\0';
        *f = fopen(nf, "r");
        if (*f == NULL)
		{
            count_error += 1;
            if (check_error(count_error)) exit(0);
            printf("Loi mo file! Vui long nhap lai.\n\n");
        }
		else valid = 1;
    }
}

int read_matrix_from_file(FILE *f, int *n, MT a)
{
    if (fscanf(f, "%d", n) != 1 || *n <= 0)
	{
        printf("Kich thuoc ma tran khong hop le!");
        return 0;
    }

    int i, j;
    for (i = 1; i <= *n; i++)
	{
        for (j = 1; j <= *n + 1; j++)
		{
            if (fscanf(f, "%f", &a[i][j]) != 1)
			{
                printf("Loi dinh dang ma tran!");
                return 0;
            }
        }
    }

    if (fgetc(f) != EOF)
	{
        printf("Loi dinh dang ma tran!");
        return 0;
    }

	setcolor(0, 10);
    printf("\nDoc du lieu tu file thanh cong!!");
    setcolor(0, 15);
    newline;
    return 1;
}

void read_matrix_from_keyboard(int n, MT a)
{
	printf("Moi nhap ma tran kich co %d x %d: \n",n,n+1);
	int i,j;
	for (i=1;i<=n;i++)
		for (j=1;j<=n+1;j++) scanf("%f",&a[i][j]);
	getchar();
	printf("\n");
}

void Print(int n, MT a, int c) //1: cramer, ko in
{
    int i, j, k;
    k = (c == 1) ? n : n + 1;
    for (i = 1; i <= n; i++)
	{
        for (j = 1; j <= k; j++)
		{
            printf("%10.3f  ", value(a[i][j]));
        }
        newline;
    }
    printf("\n");
}

void Print_file(FILE *f, int n, MT a)
{
    int i, j;
    for (i = 1; i <= n; i++)
	{
        for (j = 1; j <= n + 1; j++)
		{
            fprintf(f, "%10.3f  ", value(a[i][j]));
        }
        fprintf(f, "\n\n");
    }
    fprintf(f, "\n");
}

void copy(int n, MT a, MT A)
{
    int i, j;
    for (i = 1; i <= n; i++)
	{
        for (j = 1; j <= n + 1; j++) a[i][j] = A[i][j];
    }
}

void find_mt(MT a, MT b, int n, int c)
{
    int i, j;
    for (i = 1; i <= n; i++)
	{
        for (j = 1; j <= n; j++)
		{
            if (j == c) b[i][j] = a[i][n + 1];
            else b[i][j] = a[i][j];
        }
    }
}

void swap(int p, int q, MT a, int n) { // doi hai dong
    int i;
    float tam;
    for (i = 1; i <= n + 1; i++) {
        tam = a[p][i];
        a[p][i] = a[q][i];
        a[q][i] = tam;
    }
}

void upper_triangle_maxtrix(int n, MT a, float *dt, int pr)
{
    int i, j, l, k;
    float d;
    int count = 0; // dem so lan swap
    for (i = 1; i <= n - 1; i++)
	{
        if (pr == 1) printf("  + Bien doi ve ma tran tren o dong thu %d\n\n", i + 1);;
        if (a[i][i] == 0)
		{
            j = i;
            do 
			{
                j++; // con khac khong thi con nhin, hoac het dong de nhin
            } while (a[j][i] == 0 && j <= n);
            if (j <= n) 
			{
                if (pr == 1) printf("(Doi dong %d va dong %d cho nhau)\n\n", i, j);
                swap(i, j, a, n);
                count++;
            }
			else
			{
                if (pr == 1) Print(n, a, 0);
                continue;
            }
        }
        for (l = i + 1; l <= n; l++)
		{
            d = -a[l][i] / a[i][i];
            for (k = i; k <= n + 1; k++) a[l][k] += a[i][k] * d;
        }
        if (pr == 1)
		{
            Print(n, a, 0);
        }
    }
    if (pr == 0)
	{
        *dt = (count % 2 == 0) ? 1 : -1;
        for (i = 1; i <= n; i++) *dt *= a[i][i];
    }
}

void rank(MT a, int n, int *rA, int *rA2)
{
    int i, j;
    int rankA = n, rankA2 = n;
    int allZero;

    for (i = n; i >= 1; i--)
	{
        allZero = 1;
        for (j = 1; j <= n; j++)
		{
            if (fabs(a[i][j]) > TOLERANCE)// khac khong
			{
                allZero = 0;
                break;
            }
        }
        if (allZero) {
            rankA--;
            if (fabs(a[i][n+1]) <= TOLERANCE) // TOAN KHONG
			{
                rankA2--;
            }
        }
    }
    *rA = rankA;
    *rA2 = rankA2;
}

int solve_Cramer(MT a, int n, float x[])
{
    int j;
    MT b;
    float d, dj;
    float *dt;

	setcolor(0, 14);
	printf("              Ma tran A la:              ", j);
	setcolor(0, 15);
	newline;
    find_mt(a, b, n, n + 1);
    Print(n, b, 1);
    upper_triangle_maxtrix(n, b, dt, 0);
    d = *dt;
    printf("     Dinh thuc cua ma tran D la: %0.3f", value(d));
    newline;
    
    if (!value(d)) return 0;
    else
	{
        for (j = 1; j <= n; j++)
		{
        	setcolor(0, 14);
            printf("              Ma tran A%d la:              ", j);
            setcolor(0, 15);
            newline;
            find_mt(a, b, n, j);
            Print(n, b, 1);
            upper_triangle_maxtrix(n, b, dt, 0);
            dj = *dt;
            printf("     Dinh thuc cua ma tran D%d la: %0.3f", j, value(dj));
            newline;
            x[j] = dj / d;
            printf("     => x[%d] = D%d / D = %0.3f", j, j, value(dj));
            printf(" / %0.3f = ", d);
            printf("%0.3f", value(x[j]));
            newline;
            printf("\n");
        }
    }
    return 1;
}


void show_value(int n, float a[])
{
    int i;
    printf("       Nghiem cua he phuong trinh la:       ");
    newline;
    for (i = 1; i <= n; i++) 
	{
        printf("           x[%d]     = %10.3f  \n", i, value(a[i]));
    }
    newline;
}

void show_value_file(FILE *f, int n, float a[])
{
    int i;
    fprintf(f, "       Nghiem cua he phuong trinh la:       ");
    fprintf(f, "\n\n");
    for (i = 1; i <= n; i++)
	{
        fprintf(f, "           x[%d]     = %10.3f  \n", i, value(a[i]));
    }
    fprintf(f, "\n\n");
}

void find_value(int n, MT a, float x[])
{
    int i, j;
    float s;
    for (i = n; i >= 1; i--)
	{
        s = 0;
        for (j = i + 1; j <= n; j++) s += a[i][j] * x[j];
        x[i] = (a[i][n + 1] - s) / a[i][i];
    }
}

float value(float x)
{
    if (fabs(x) <= TOLERANCE) return 0.00;
    else return x;
}


void write_file()
{
    printf("Nhap ten file (xuat ket qua): ");
    char file[MAX];
    fgets(file, MAX, stdin);
    file[strcspn(file, "\n")] = '\0';
	printf("---------------------------------------\n");
	            
    FILE *F = fopen(file, "a");
    FILE *RES = fopen("KETQUA.TXT", "r");

    if (F == NULL || RES == NULL)
	{
        printf("Loi khi mo file!\n");
        return;
    }

    char ch;

    while ((ch = fgetc(RES)) != EOF)
	{
        printf("%c", ch);
        fputc(ch, F);
    }

    fclose(RES);
    fclose(F);

	setcolor(0, 14);
    printf("DA LUU KET QUA VAO FILE THANH CONG\n");
	setcolor(0, 10);
}

