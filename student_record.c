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
    printf("\n\t\t\tID\t\t\tName\t\t\tAge\t\t\tDepartment\t\tGPA\n");
    for (const student* student = head; student != NULL; student = student->next){
        printf("\t\t\t%d\t\t\t%s\t\t\t%d\t\t\t%s\t\t\t%.2f\n", student->id, student->name,student->age, student->department, student->gpa);
        printf("\t\t\t----------------------------------------------------------------------------------------------------\n");
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
        fprintf(file, "%d,\t\t%s|\t\t%d|\t\t%s|\t\t%.2f|\n", student->id, student->name,student->age, student->department, student->gpa);
    }
    fclose(file);
}

//this is the function to do sorting og records, we are going to use bubble sort to handle it
void sortrecord(struct student* head){
    if(head == NULL) return;
    int swapped;
    struct student* temp;
    struct student* lptr = NULL;
    do{
        swapped = 0;
        temp = head;

        while(temp->next != lptr){
            if(temp->id > temp->next->id){
                //we  Swap ID
                int holdId = temp->id;
                temp->id = temp->next->id;
                temp->next->id = holdId;

                // and the Swap Name
                char holdName[50];
                strcpy(holdName, temp->name);
                strcpy(temp->name, temp->next->name);
                strcpy(temp->next->name, holdName);

                // and also the Swap Age
                int holdAge = temp->age;
                temp->age = temp->next->age;
                temp->next->age = holdAge;

                // the Swap Department section
                char holdDept[50];
                strcpy(holdDept, temp->department);
                strcpy(temp->department, temp->next->department);
                strcpy(temp->next->department, holdDept);

                // Swap GPA
                float holdGpa = temp->gpa;
                temp->gpa = temp->next->gpa;
                temp->next->gpa = holdGpa;

                swapped = 1;
            }
            temp = temp->next;
        }
        lptr = temp;
    }while(swapped);

}

//this is the fuction to check  max and min and avrage of the student records

void checkstatistics(const student* head){
    if (head == NULL){
        printf("No student records found.\n");
        return;
    }

    int max_age = head->age;
    int min_age = head->age;
    float max_gpa = head->gpa;
    float min_gpa = head->gpa;
    float sum_gpa = 0;
    int sum_age = 0;
    int count = 0;

    for(const student* current = head; current != NULL; current = current->next){
        if(current->age > max_age) max_age = current->age;
        if(current->age < min_age) min_age = current->age;
        if(current->gpa > max_gpa) max_gpa = current->gpa;
        if(current->gpa < min_gpa) min_gpa = current->gpa;
        sum_gpa += current->gpa;
        sum_age += current->age;
        count++;
    }

    printf("\n=== Student Records Statistics ===\n");
    printf("Total Students: %d\n", count);
    printf("Age Statistics:\n");
    printf("  - Maximum Age: %d\n", max_age);
    printf("  - Minimum Age: %d\n", min_age);
    printf("  - Average Age: %.1f\n", (float)sum_age / count);
    printf("GPA Statistics:\n");
    printf("  - Maximum GPA: %.2f\n", max_gpa);
    printf("  - Minimum GPA: %.2f\n", min_gpa);
    printf("  - Average GPA: %.2f\n", sum_gpa / count);
    printf("==================================\n");
}

// function to search for a student by name (case-insensitive)
student* searchstudentbyname(student* head, const char* name){
    student* current = head;
    while(current != NULL){
        if(strcasecmp(current->name, name) == 0){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//finally 
//before i continue don't mind i will explain everything the head thing and all

int main(){
    // all we do now is call the functions
    student* head = NULL;
    int Password = 0;
    while (1) {
        printf("Enter system password: ");
        if (scanf("%d", &Password) == 1) {
            if (Password == 1234) {
                break;
            } else {
                printf("Incorrect password! Please try again.\n");
            }
        } else {
            printf("Invalid input! Please enter numbers only.\n");
            // Clear the invalid input from the buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }


    while (1){
        printf("\n Student Record Management System\n");
        printf("1. Add student\n");
        printf("2. Display Student\n");
        printf("3. Search Student by ID\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Save Data to File\n");
        printf("7. Sort the student record\n");
        printf("8. Check Statistics\n");
        printf("9. Search Student by Name\n");
        printf("10. Exit\n");

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
            printf("\nsuccesfully added student to data database!\n");
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
            printf("Student records successfully sorted by ID.\n");
            break;
        case 8:
            checkstatistics(head);
            break;
        case 9: {
            char searchname[50];
            printf("Enter Student Name to search: ");
            scanf("%s", searchname);
            student* foundstudent = searchstudentbyname(head, searchname);
            if(foundstudent != NULL){
                printf("Student found:\n");
                printf("ID: %d\nName: %s\nAge: %d\nDepartment: %s\nGPA: %.2f\n", foundstudent->id, foundstudent->name, foundstudent->age, foundstudent->department, foundstudent->gpa);
            }else{
                printf("Student not found.\n");
            }
            break;
        }
        case 10:
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