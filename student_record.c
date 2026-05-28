// all this code was written by Joel Achiangah Fombin # @copywork
// hello today we are going to learn some cool stuff in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// step one is to create the student data type
typedef struct student{
    int id;
    char name[50];
    int age;
    char department[50];
    float gpa;
    struct student *next;
}student;
//done 
//now we need a link list or a node
//this is the function to create a new student node
student* createstudent(int id, const char* name, int age, const char* department, float gpa){
    student* newNode = (student*)malloc(sizeof(student));
    if(newNode == NULL){
        fprintf(stderr, "Memory allocation failed(lol)\n");
        exit(1);
    }
    newNode->id = id;
    strcpy(newNode-> name, name);
    newNode->age = age;
    strcpy(newNode->department, department);
    newNode->gpa = gpa;
    newNode->next = NULL;
    return newNode;
}

//function to add a new student 
void addstudent(student** head, student* newstudent){
    if(*head == NULL){
        *head = newstudent;
    }else{
        student* current = *head;
        while (current -> next != NULL){
            current = current->next;
        }
        current->next = newstudent;
    }
}
//done(lol)
//now we add the function to delete a student by ID cuz well.... i want it like that(lol)
void deletestudent(student** head, int id){
    if(*head == NULL) return;
    student* temp = *head;
    student* prev = NULL;

    if(temp != NULL && temp->id == id){
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->id !=id){
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}
//so far so good, no error massages
//now to add the function to update a student by ID
void updatestudent(student** head, int id, const char*name, int age, const char* department, float gpa){
    student* current = *head;
    while (current !=NULL && current->id !=id){
        current = current->next;
    }

    if(current == NULL)return;
    //i should type it again that what should happen(lol)
    strcpy(current-> name, name);
    current->age = age;
    strcpy(current->department, department);
    current->gpa = gpa;
    
}
// function to display all the student that are searched by id (english ohhlol)
student* searchstudent(student* head, int id){
    student* current = head;
    while(current != NULL && current->id != id){
        current = current-> next;
    }
    return current;
}
//done ya!!
// ok now the function to display all students in the linked list
void displaystudent(const student* head){
    printf("ID\tName\tAge\tDepartment\tGPA\n");
    for (const student* student = head; student != NULL; student = student->next){
        printf("%d\t%s\t%d\t%s\2t%.2f\n", student->id, student->name,student->age, student->department, student->gpa);
    }
    
}
// the bonus task them
//this is the function to save data to a file
void savedata(const student* head, const char* filename){
    FILE* file = fopen(filename, "w");
    if(file == NULL){
        fprintf(stderr, "Could not open file for writing.\n");
        return;
    }
    fprintf(file, "student id | student Name| student age | student department | student GPA\n");
    for (const student* student = head; student != NULL; student = student->next){
        fprintf(file, "%d,%s,%d,%s,%.2f\n", student->id, student->name,student->age, student->department, student->gpa);
    }
    fclose(file);
}

//this is the function to do sorting og records, we are going to use bubble sort to handle it
void sortrecord(struct student* head){
    int swapped;
    struct student* temp;
    struct student* prev = NULL;
    do{
        swapped = 0;
        temp = head;

        while(temp->next != NULL){
            if(temp->id > temp->next->id){
                int hold = temp->id;
                temp->id = temp->next->id;
                temp->next->id = hold;
                swapped = 1;
            }
            temp = temp->next;
        }
        temp = prev;
    }while(swapped);

}

//finally 
//before i continue don't mind i will explain everything the head thing and all

int main(){
    // all we do now is call the functions
    student* head = NULL;
    int Password;
    do{
    printf("Enter system password: ");
    scanf("%d", &Password);
    }while (Password != 1234); 


    while (1){
        printf("\n Student Record Management System\n");
        printf("1. Add student\n");
        printf("2. Display Student\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Save Data to File\n");
        printf("7. Sort the student record\n");
        printf("8. Exit\n");

        int choice;
        scanf("%d", &choice);

        switch (choice){
        case 1:
            // now this one will be.... to.. add students
            int id, age;
            char name[50], department[50];
            float gpa;

            printf("Enter Student ID: ");
            scanf("%d", &id);
            printf("Enter Student Name: ");
            scanf("%s", name);
            printf("Enter Student age: ");
            scanf("%d", &age);
            printf("Enter Student Department: ");
            scanf("%s", department);
            printf("Enter Student GPA: ");
            scanf("%f", &gpa);

            //now to to sent the info to the linked list, massa me am tired ya
            student* newstudent = createstudent(id, name, age, department, gpa);
            addstudent(&head, newstudent);
            printf("succesfully added student to data database!");
            break;
        case 2:
            // to display the student
            displaystudent(head);// lemme just finish then we check and debug the code 1hr break abeg, i will be back bye
            break;
        case 3:
            // to search for a student by id
            int searchid;
            printf("Enter Student ID to search: ");
            scanf("%d", &searchid);
            student* foundstudent = searchstudent(head, searchid);
            if(foundstudent != NULL){
                printf("Student found:\n");
                printf("ID: %d\nName: %s\nAge: %d\nDepartment: %s\nGPA: %.2f\n", foundstudent->id, foundstudent->name, foundstudent->age, foundstudent->department, foundstudent->gpa);
            }else{
                printf("Student not found.\n");
            }
            break;
            //am so sorry you'll
        case 4:
            // to update a student by id
            int updateid;
            char newname[50], newdepartment[50];
            int newage;
            float Newgpa;


            printf("Enter Student ID to update: ");
            scanf("%d", &updateid);
            printf("Enter new Student Name: ");
            scanf("%s", newname);
            printf("Enter new Student age: ");
            scanf("%d", &newage);
            printf("Enter new Student Department: ");
            scanf("%s", newdepartment);
            printf("Enter new Student GPA: ");
            scanf("%f", &Newgpa);

            updatestudent(&head, updateid, newname, newage, newdepartment, Newgpa);
            break;
        case 5:
            // to delete a student by id
            int deleteid;
            printf("Enter Student ID to delete: ");
            scanf("%d", &deleteid);
            deletestudent(&head, deleteid);
            printf("Student with ID %d deleted.\n", deleteid);
            //AI is scary
            break;
        case 6: {
            char filename[50];
            printf("Enter a file name to save: ");
            scanf("%s", filename);
            savedata(head, filename);
            break;
        }
        case 7:
            sortrecord(head);
        case 8:
            // to exit the program
            printf("Exiting the program. Goodbye!\n");
            exit(0);
            break;
            
        
        default:
            //sorry my data is on so the ai will assist me in writing the code (lol)
            printf("Invalid choice, please try again.\n");
            break;
        }
    }
    
    return 0;
}