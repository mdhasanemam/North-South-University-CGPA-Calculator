#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Course
{
    char courseName[20];
    int credit;
    int marks;
    double grade;
};
#define Course struct Course

char global_name[10], global_password[10], global_username[10];
int global_Id;

void write_cgpa(double cgpa)
{
    FILE *to_write = fopen("temp.txt","w");
    FILE *to_read = fopen("user.txt","r");

    char u_name[10],u_pass[10],username[10],pass[10],name[200], gpa[15];
    int id;

    if(to_write != NULL && to_read != NULL)
    {
         while(fscanf(to_read,"%s\n%d\n%s\n%s\n%s\n",name,&id, pass, username, gpa) != EOF )
        {
            //printf("\nName: %s ID: %d Password: %s Username: %s GPA: %s\n",name,id,pass, username, gpa);
            if((strcmp(global_username,username)) == 0 && (strcmp(global_password,pass)) == 0)
            {
               fprintf(to_write,"%s\n%d\n%s\n%s\n%.2lf\n",name,id,pass,username,cgpa);
            }
            else
            {
                fprintf(to_write,"%s\n%d\n%s\n%s\n%s\n",name,id,pass,username,gpa);
            }
        }
    }
    else{
        printf("ERROR!!!");
    }

    fclose(to_write);
    fclose(to_read);
    remove("user.txt");
   if(rename("temp.txt", "user.txt") != 0) {
      printf("ERROR!!!");
   }
}


void cgpa()
{
	FILE *fptr;
	fptr = fopen("courseInfo.txt", "r");
	char name[20];
	int marks, credit, j = 0;
	Course courses[8];
	while(fscanf(fptr,"%s %d %d\n",name, &credit, &marks) != EOF)
    {
        //printf("%s %d %d\n", name, credit, marks);

        double grade;
        if(marks>=93) grade = 4.0;
        else if(marks >= 90) grade = 3.7;
        else if(marks >= 87) grade = 3.3;
        else if(marks >= 83) grade = 3.0;
        else if(marks >= 80) grade = 2.7;
        else if(marks >= 77) grade = 2.3;
        else if(marks >= 73) grade = 2.0;
        else if(marks >= 70) grade = 1.7;
        else if(marks >= 67) grade = 1.3;
        else if(marks >= 60) grade = 1.0;
        else grade = 0.0;

        strcpy(courses[j].courseName, name);
        courses[j].credit = credit;
        courses[j].marks = marks;
        courses[j].grade = grade;

        j++;
    }

    int total_credit = 0;
    int sum = 0;
    printf("\n\nCourse Name\tCredit\tMark\tGarde\n");
    for(int i = 0; i< j; i++)
    {
        printf(" %s\t\t%d\t%d\t%.2lf\n",courses[i].courseName,courses[i].credit, courses[i].marks, courses[i].grade);


        sum += courses[i].credit * courses[i].grade;
        total_credit += courses[i].credit;
    }
    double cgpa = (double)sum/(double)total_credit;
    printf("\n\t\tYour CGPA is: %.2lf", cgpa );
    //printf("\n\n");
    write_cgpa(cgpa);
}
void courseinfo()
{

	int number, value;

	printf("\nEnter How many course you want to calcuate CGPA: ");
	scanf("%d", &number);
    FILE *fptr;
    fptr = fopen("courseInfo.txt", "w");
	for(int i=0;i<number;i++)
	{
	   // printf("I am here line 40\n");
	    char course_name[20];
	    int credit, marks;

		printf("\nEnter Course %d.No name: ",i+1);
	    scanf("%s", course_name);
	    printf("Enter credit of %s: ", course_name);
	    scanf("%d", &credit);
	    printf("Enter marks of %s: ",course_name);
	    scanf("%d", &marks);

       // printf("I am here line 50\n");



	    fprintf(fptr,"%s %d %d\n", course_name, credit, marks);

	   // printf("I am here line 57\n");

	}
    fclose(fptr);

	printf("\nDo you wanto check cgpa? \n1. Yes\n2. No\ninput: ");
	scanf("%d", &value);
	if(value==1)
	{
		cgpa();

	}

    printf("\n\nYou Are Logged Out\n\n");
}

void login()
{
    printf("\n\t\t*****Login Panel*****\n\n");
	int i=0,id;
	char u_name[10],u_pass[10],username[10],pass[10],name[200], gpa[15];
	gets(stdin);
	printf("Enter username: ");
	gets(u_name);
	printf("Enter password: ");
	gets(u_pass);
	FILE *fptr;
	fptr = fopen("user.txt", "r");
    int check = 0;
    while(fscanf(fptr,"%s\n%d\n%s\n%s\n%s\n",name,&id, pass, username, gpa) != EOF )
    {
        //printf("\nName: %s ID: %d Password: %s Username: %s GPA: %s\n",name,id,pass, username, gpa);
        if((strcmp(u_name,username)) == 0 && (strcmp(u_pass,pass)) == 0)
        {
            check = 1;
           // fprintf(fptr,"I am here\n");
            break;
        }
    }

    fclose(fptr);
	if(check)
    {
    	//printf("Login Successfull!!\n");
        //printf("\nName: %s\nID: %d\nUsername: %s\nCGPA: %s\n",name,id,username, gpa);
        strcpy(global_name, name);
        strcpy(global_password, pass);
        global_Id = id;
        strcpy(global_username, username);

        printf("\n\t\t*****Login successfull*****\n\n", global_name);
        printf("Account Information:\n");
        printf("\tName: %s\n", global_name);
        printf("\tID %d\n", global_Id);
        printf("\tUsername: %s\n",global_username);
        if(strcmp(gpa,"invalid") != 0)
            printf("\tCGPA: %s\n", gpa);
        else
            printf("\tCGPA: No Previous Data!\n");


        courseinfo();
    }
    else
    {
        printf("Wrong Credentials. Please try again!\n\n");
        //login();
    }
}
void registration()
{
    printf("\n\t\t*****Registration Panel*****\n\n");

	char name[200],username[10],pass[10];
	int id,i=0;
	gets(stdin);
	printf("Enter Name: ");
	gets(name);
	printf("Enter ID: ");
	scanf("%d",&id);
	gets(stdin);
	while(((strlen(pass)<6) || ((strlen(pass))>10)))
	{
		printf("Take password that contains at least 6 characters and not more than 10 characters.\n");
		printf("Enter Password: ");
	    gets(pass);
		i++;
	}
	while(((strlen(username)<5) || ((strlen(username))>10)))
	{
		printf("Take username at least of 5 characters and not more than 10 characters.\n");
		printf("Enter Username: ");
	    gets(username);
		i++;
	}

	FILE *fptr;
	fptr = fopen("user.txt","a");
	if(fptr==NULL)
	{
		printf("File not opened.\n\n");
	}
	else
	{

		//printf("File opened successfully.");

		fprintf(fptr,"%s\n%d\n%s\n%s\n%s\n",name,id,pass,username,"invalid");
	    fclose(fptr);
        printf("Congratulations! Registration sucessfull.\n\n");
	}
}
void main()
{
    printf("\t\t\t*****NSU CGPA CALCULATOR*****\n\n");
	while(1)
    {
        int value;
        printf("1. Login\n");
        printf("2. Registration\n");
        printf("3. Exit\n");
        printf("Choose a option: ");
        scanf("%d",&value);
        if(value == 1)
        {
            login();
        }
        else if(value == 2)
        {
            registration();
        }
        else if(value == 3)
        {
            break;
        }
        else
        {
            printf("\nPlease choose correct option\n\n");
        }
    }
    printf("\n\n\t\t*****THANK YOU FOR USING NSU CGPA CALCULATOR*****\n\n");
}

