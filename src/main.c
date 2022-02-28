#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define LENNAME 16
#define MAX_COURSES 4
#define MAX_STUDENT 30

//select sort. method
enum sorting_method {ascending, descending};

struct data {
    // student ID
    long id;
    // the student's name
    char name [LENNAME];
    // academic performance
    int test_res [MAX_COURSES];
    // overall result
    int total;
    // average result
    float average;
};

// shows the menu and accepts the user's choice
int showmenu(void);
// reads an integer between two values
long read_long_between (long min, long max);
// clears the string
void eatline(void);
// reads a string
char * f_gets (char * st, int n);

// reads the data about the students
void Input (struct data pt[], int n_cour, int n_stu, char crs_name[][LENNAME]);
// counts and displays the total value and average score of each course
void total_av_courses (struct data pt[], int n_cour, int n_stu, char crs_name[][LENNAME]);
// counts and displays the total value and average score of each student
void total_av_student (struct data pt[], int n_stu);
// sorts students according to the overall result (ascending or descending)
void sort_score (struct data pt[], int n_stu, int des_asc);
// sorts students according to ID (ascending or descending)
void sort_id (struct data pt[], int n_stu, int des_asc);
// sorts students by name in alphabetical order
void sort_by_name (struct data pt[], int n_stu);
// student ID search
void search_by_num (struct data pt[], int n_cour, int n_stu, char crs_name[][LENNAME]);
// search for students by name
void search_by_name (struct data pt[], int n_cour, int n_stu, char crs_name[][LENNAME]);
// output of students ' progress statistics for each course
void statistic (struct data pt[], int n_cour, int n_stu, char crs_name[][LENNAME]);
// output of students ' test results for each course
void showdata (struct data pt[], int n_cour, int n_stu, char crs_name[][LENNAME]);
// reads data from a file
void read_from_f (struct data pt[] ,int * n_cour, int * n_stu, char crs_name[][LENNAME]);
// writes data to a file
void write_to_f (struct data pt[], int n_cour, int n_stu, char crs_name[][LENNAME]);

int main ()
{
    int n_courses;  // number of courses
    int n_students; // number of students
    struct data students_data[MAX_STUDENT];
    char course_name[MAX_COURSES][LENNAME];

    puts("If you would like to upload a progress file, please write <Y/y>");
    puts("Enter any other character to skip and start filling.");
    char ch = getchar();
    if(ch == 'Y' || ch == 'y')
    {
        getchar();//carriage, возврат каретки
        goto RFF;
    }

    printf ("Enter students number:\n>");
    n_students = read_long_between (1, MAX_STUDENT);

    printf ("Enter courses number:\n>");
    n_courses = read_long_between (1, MAX_COURSES);

    int choise;
    int found;
    while ((choise = showmenu()) != 0)/* -> if you enter 0, the program terminates */
    {
        switch (choise)
        {
            case 1:  Input (students_data, n_courses, n_students, course_name); break;
            case 2:  total_av_courses (students_data, n_courses, n_students, course_name); break;
            case 3:  total_av_student (students_data, n_students); break;

            case 4:  sort_score (students_data, n_students, descending);
                     total_av_student (students_data, n_students); break;

            case 5:  sort_score (students_data, n_students, ascending);
                     total_av_student (students_data, n_students); break;

            case 6:  sort_id (students_data, n_students, descending);
                     total_av_student (students_data, n_students); break;

            case 7:  sort_id (students_data, n_students, ascending);
                     total_av_student (students_data, n_students); break;

            case 8:  sort_by_name   (students_data, n_students);
                     total_av_student (students_data, n_students); break;

            case 9:  search_by_num  (students_data, n_courses, n_students, course_name); break;
            case 10: search_by_name (students_data, n_courses, n_students, course_name); break;
            case 11: statistic (students_data, n_courses, n_students, course_name); break;
            case 12: showdata (students_data, n_courses, n_students, course_name); break;
            case 13: write_to_f (students_data, n_courses, n_students, course_name); break;
            RFF:
            case 14: read_from_f (students_data, &n_courses, &n_students, course_name);
                     showdata (students_data, n_courses, n_students, course_name); break;
        }
    }
    puts ("Programm is over.");

    return 0;
}
int showmenu (void)
{
    int ans;
    puts ("\n Enter the selected option from the menu:");
    puts (" (1) Input record");
    puts (" (2) Calculate total and average score of every course");
    puts (" (3) Calculate total and average score of every student");
    puts (" (4) Sort in descending order by total score of every student");
    puts (" (5) Sort in ascending order by total score of every student ");
    puts (" (6) Sort in descending order by number ");
    puts (" (7) Sort in ascending order by number ");
    puts (" (8) Sort in dictionary order by name");
    puts (" (9) Search by number");
    puts (" (10) Search by name");
    puts (" (11) Statistic analysis for every course");
    puts (" (12) List record (detailed results)");
    puts (" (13) Write to a file ");
    puts (" (14) Read from a file");
    puts (" (0) Exit ");
    printf(">");
    ans = read_long_between (0, 14);
    return ans;
}

void Input (struct data pt [], int n_cour, int n_stu, char crs_name[][LENNAME])
{
    system("cls");      // clear the screen
    int i=0, j;
    while (i < n_cour)
    {
        printf ("Input name of %d course:\n>", i+1);
        f_gets(crs_name[i], LENNAME);
        i++;
    }

    for (i=0; i<n_stu; i++)
    {
        int total=0;
        printf ("Input student`s %d ID (100000000 - 999999999):\n >", i+1);
        pt[i].id = read_long_between (100000000, 999999999);
        printf ("Input student`s name:\n>");
        f_gets(pt[i].name, LENNAME);
        for (j = 0; j < n_cour; j++)
        {
            printf ("Enter the results of the student %s on the course %s\n",
                    pt[i].name, crs_name[j]);
            total += pt[i].test_res[j] = read_long_between(0,100);
        }
        pt[i].total = total;
        pt[i].average = (float)total/j;
    }
    printf ("\n");
}

long read_long_between (long min, long max)
{
    int countErr;
    long number;
    bool integer;
                    // get an answer
    while ((integer = scanf ("%d", &number)) != 1 ||
            number < min || number > max)
    {
        if (integer != 1)
        {
            countErr++;
            printf("[ERROR (%d/15)]: Enter an integer number\n", countErr);
            // If the number of input errors exceeds 15 times, display a notification and exit the program
            // After correct entry, the counter is automatically reset to zero
            if (countErr == 15)
            {
                puts("[ATTENTION]: Dear Sr/Ms. Please Enter an integer number. Try running the program again. Bye bye!");
                exit (EXIT_SUCCESS);
            }
        }
        else
        {
            printf ("The number must be between %d - %d\n", min, max);
        }
        // get rid of the rest of the line
        eatline ();
    }
    eatline ();
    return number;
}

void eatline (void)
{
    while (getchar() != '\n')
        continue;
}

char * f_gets (char * st, int n)
{
    char * ret_val;
    char * find;
    ret_val = fgets (st, n, stdin);
    if (ret_val)
    {
        find = strchr (st, '\n');       // search for newline character
        if (find)                       // if address is not NULL
            *find = '\0';               // put a null character there
        else
            eatline();    // discard the rest of the line
    }
    return ret_val;
}

void showdata (struct data pt [], int n_cour, int n_stu, char crs_name[][LENNAME])
{
    int i,j;
    system("cls");        // clear the screen
    printf ("ID        Name of student");
    for (j=0; j < n_cour; j++)
        printf ("%12s", crs_name[j]);
    printf ("\n");

    for (i=0; i < n_stu; i++)
    {
        printf ("%d ",   pt[i].id);
        printf ("%-15s", pt[i].name);
        for (j=0; j<n_cour; j++)
            printf ("%12d", pt[i].test_res[j]);
        printf ("\n");
    }
    printf ("\n");
}

void total_av_courses(struct data pt [], int n_cour, int n_stu, char crs_name[][LENNAME])
{
    system("cls");
    printf ("        ");
    int i,j;

    for (i=0; i<n_cour; i++)
        printf ("%15s", crs_name[i]);
    printf ("\nTotal:  ");

    float aver[n_cour];
    for (j=0; j<n_cour; j++)
    {
        int tot = 0;
        for (i=0; i<n_stu; i++)
            tot += pt[i].test_res[j];
        printf ("%15d", tot);
        aver[j] = (float)tot/n_stu;
    }

    printf ("\nAverage:");
    for (i=0; i<n_cour; i++)
        printf ("%15.2f", aver[i]);
    printf ("\n");
}

void total_av_student(struct data pt [], int n_stu)
{
    int i,j;
    system("cls");
    //printf ("ID        Name of student          Total        Average\n");
    puts(" ___________________________________________________________");
    puts("|           |                  |           |                |");
    puts("|     ID    | Name of student  |   Total   |      Average   |");
    puts("|___________|__________________|___________|________________|");
    for (i=0; i < n_stu; i++)
        printf ("|%11d|%18s|%11d|%16f|\n", pt[i].id, pt[i].name, pt[i].total, pt[i].average);
    printf ("\n");
}

void sort_score (struct data pt [], int n_stu, int des_asc)
{
    int j, i;
    for (j=0;j<n_stu;j++)
    {
        for (i=0;i<n_stu-1;i++)
        {
            // select sorting method
            if (des_asc == descending)
            {
                if (pt[i].total<pt[i+1].total)
                {
                    struct data temp;
                    temp=pt[i+1];
                    pt[i+1]=pt[i];
                    pt[i]=temp;
                }
            }
            else if (des_asc == ascending)
            {
                if (pt[i].total>pt[i+1].total)
                {
                    struct data temp;
                    temp=pt[i+1];
                    pt[i+1]=pt[i];
                    pt[i]=temp;
                }
            }
        }
    }
}

void sort_id (struct data pt [], int n_stu, int des_asc)
{
    int j, i;
    for (j=0;j<n_stu;j++)
    {
        for (i=0;i<n_stu-1;i++)
        {
            // select sorting method
            if (des_asc == descending)
            {
                if (pt[i].id<pt[i+1].id)
                {
                    struct data temp;
                    temp=pt[i+1];
                    pt[i+1]=pt[i];
                    pt[i]=temp;
                }
            }
            else if (des_asc == ascending)
            {
                if (pt[i].id>pt[i+1].id)
                {
                    struct data temp;
                    temp=pt[i+1];
                    pt[i+1]=pt[i];
                    pt[i]=temp;
                }
            }
        }
    }
}


void sort_by_name (struct data pt[], int n_stu)
{
    int j, i;
    for (j=0;j<n_stu;j++)
    {
        for (i=0;i<n_stu-1;i++)
        {
            if (strcmp(pt[i].name, pt[i+1].name) > 0)
            {
                struct data temp;
                temp=pt[i+1];
                pt[i+1]=pt[i];
                pt[i]=temp;
            }
        }
    }
}
void search_by_num (struct data pt [], int n_cour, int n_stu, char crs_name[][LENNAME])
{
    int i;
    int counter = 0;
    long s_id;
    printf ("Enter student's ID (100000000 - 999999999):\n>");
    s_id = read_long_between (100000000, 999999999);
    system("cls");
    for (i=0; i < n_stu; i++)
        if (pt[i].id == s_id)
        {
            int j;
            if (counter == 0)
            {
                printf ("ID        Name of student");
                for (j=0; j < n_cour; j++)
                    printf ("%12s", crs_name[j]);
                printf ("\n");
            }
            printf ("%d ", pt[i].id);
            printf ("%-15s", pt[i].name);
            for (j=0; j<n_cour; j++)
                printf ("%12d", pt[i].test_res[j]);
            printf ("\n");
            counter++;
        }
    if (counter == 0)
        puts ("Not found.");
    printf ("\n");
}

void search_by_name (struct data pt [], int n_cour, int n_stu, char crs_name[][LENNAME])
{
    int i;
    int counter=0;
    char s_id[LENNAME];
    printf ("Enter student's name:\n>");
    f_gets(s_id, LENNAME);
    system("cls");
    int size = strlen(s_id);
    for (i=0; i < n_stu; i++)
        if (strncmp(s_id, pt[i].name, size) == 0)
        {
            int j;
            if (counter == 0)
            {
                printf ("ID        Name of student");
                for (j=0; j < n_cour; j++)
                    printf ("%12s", crs_name[j]);
                printf ("\n");
            }
            printf ("%d ", pt[i].id);
            printf ("%-15s", pt[i].name);
            for (j=0; j<n_cour; j++)
                printf ("%12d", pt[i].test_res[j]);
            printf ("\n");
            counter++;
        }
    if (counter == 0)
        puts ("Not found.");
    printf ("\n\n");
}


void statistic (struct data pt [], int n_cour, int n_stu, char crs_name[][LENNAME])
{
    system("cls");
    int i,j,k;
    printf ("   Grades         ");
    for (j=0; j < n_cour; j++)
        printf ("%15s", crs_name[j]);
    printf ("\n\n");
    for (i=0; i<5; i++)
    {
        switch (i)
            {
                case 0: printf ("Excellent (90-100)"); break;
                case 1: printf ("     Good  (80-89)"); break;
                case 2: printf ("   Medium  (70-79)"); break;
                case 3: printf ("     Pass  (60-69)"); break;
                case 4: printf ("     Fail   (0-59)"); break;
            }
        for (j=0; j < n_cour; j++)
        {
            int count=0;
            for (k=0; k < n_stu; k++)
            {
                switch (pt[k].test_res[j])
                {
                    case 0 ... 59:
                        if (i == 4)
                            count++; break;
                    case 60 ... 69:
                        if (i == 3)
                            count++; break;
                    case 70 ... 79:
                        if (i == 2)
                            count++; break;
                    case 80 ... 89:
                        if (i == 1)
                            count++; break;
                    case 90 ... 100:
                        if (i == 0)
                            count++; break;
                }
            }
            printf ("%9d /%3d%%", count, (count*100)/n_stu);
        }
        printf ("\n");
    }
    printf ("\n");
}

void read_from_f (struct data  pt [] , int * n_cour, int * n_stu, char crs_name[][LENNAME])
{
    int count = 0;
    char file_name [LENNAME+4];
    FILE * fdata;
    int size = sizeof (struct data);
    printf ("Enter name of file:\n>");
    f_gets(file_name, LENNAME);
    // add an extension to the file name .dat
    strcat (file_name,".dat");
    if ((fdata = fopen(file_name, "r")) == NULL)
    {
        printf ( "Cannot open file %s\n",file_name);
        exit (0);
    }
    // go to the beginning of the file
    rewind (fdata);
    fscanf (fdata, "%d %d", n_cour, n_stu);

    int i;
    for (i=0; i<*n_cour; i++)
        fscanf (fdata, "%s ", crs_name[i]);
                                // read the structure
    while (count < *n_stu && fread(&pt[count], size, 1, fdata) == 1)
        count++;
    if (fclose (fdata) != 0)
        printf ("\nError closing file");
}

void write_to_f(struct data pt [], int n_cour, int n_stu, char crs_name[][LENNAME])
{
    int count = 0;
    char file_name [LENNAME+4];
    FILE * fdata;
    int size = sizeof (struct data);
    printf ("Enter name of file:\n>");
    f_gets(file_name, LENNAME);
    strcat (file_name,".dat");
    fdata = fopen(file_name, "w");

    rewind (fdata);
    fprintf (fdata, "%d %d", n_cour, n_stu);
    int i;
    for (i=0; i<n_cour; i++)
        fprintf (fdata, "%s ", crs_name[i]);
                            // write structures
    while (count < n_stu && fwrite(&pt [count], size, 1, fdata) == 1)
        count++;
    if (fclose (fdata) != 0)
        printf ("\nError closing file");
}
