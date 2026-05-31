// hello today we are going to learn some cool stuff in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_FILE "students.txt"

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
    strncpy(newNode->name, name, 49); newNode->name[49] = '\0';
    newNode->age = age;
    strncpy(newNode->department, department, 49); newNode->department[49] = '\0';
    newNode->gpa = gpa;
    newNode->next = NULL;
    return newNode;
}

//function to add a new student 
int addstudent(student** head, student* newstudent){
    // check for duplicate IDs first
    student* check = *head;
    while(check != NULL){
        if(check->id == newstudent->id){
            printf("Error: Student with ID %d already exists.\n", newstudent->id);
            free(newstudent);
            return 0;
        }
        check = check->next;
    }
    if(*head == NULL){
        *head = newstudent;
    }else{
        student* current = *head;
        while (current -> next != NULL){
            current = current->next;
        }
        current->next = newstudent;
    }
    return 1;
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

    if(temp == NULL){ printf("Student with ID %d not found.\n", id); return; }

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

    if(current == NULL){ printf("Student with ID %d not found.\n", id); return; }
    //i should type it again that what should happen(lol)
    strncpy(current->name, name, 49); current->name[49] = '\0';
    current->age = age;
    strncpy(current->department, department, 49); current->department[49] = '\0';
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
    printf("\n  +--------+----------------------+-----+----------------------+-------+\n");
    printf("  | %-6s | %-20s | %-3s | %-20s | %-5s |\n", "ID", "Name", "Age", "Department", "GPA");
    printf("  +--------+----------------------+-----+----------------------+-------+\n");
    if(head == NULL){
        printf("  |                      (no records found)                            |\n");
        printf("  +--------+----------------------+-----+----------------------+-------+\n");
        return;
    }
    for (const student* student = head; student != NULL; student = student->next){
        printf("  | %-6d | %-20s | %-3d | %-20s | %-5.2f |\n", student->id, student->name, student->age, student->department, student->gpa);
        printf("  +--------+----------------------+-----+----------------------+-------+\n");
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
    for (const student* student = head; student != NULL; student = student->next){
        fprintf(file, "%d,%s,%d,%s,%.2f\n", student->id, student->name,student->age, student->department, student->gpa);
    }
    fclose(file);
}
//this is the function to load data from a file
void loadfile(student** head, const char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        return; // silent on first run, file may not exist yet
    }

    char line[256]; // Increased buffer size for safety

    while(fgets(line, sizeof(line), file) != NULL){
        int id, age;
        char name[50], department[50];
        float gpa;

        // Use %[^,] to read strings containing spaces until a comma is found
        // Added width limits (e.g., %49[^,]) to prevent buffer overflow
        if(sscanf(line, "%d,%49[^,],%d,%49[^,],%f", 
                  &id, name, &age, department, &gpa) == 5){
            
            student* newstudent = createstudent(id, name, age, department, gpa);
            addstudent(head, newstudent);
        } else {
            // Optional: Print error for malformed lines
            fprintf(stderr, "Failed to parse line: %s", line);
        }
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

// free the whole list to avoid memory leaks
void freelist(student** head){
    student* current = *head;
    while(current != NULL){
        student* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// helper to read a full line so names with spaces actually work
void readline(const char* prompt, char* buf, int size){
    printf("%s", prompt);
    if(fgets(buf, size, stdin) != NULL)
        buf[strcspn(buf, "\n")] = '\0';
}

// helper to clear the input buffer
void clearbuffer(void){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
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
            clearbuffer();
            if (Password == 1234) {
                break;
            } else {
                printf("Incorrect password! Please try again.\n");
            }
        } else {
            printf("Invalid input! Please enter numbers only.\n");
            clearbuffer();
        }
    }

    // auto load records when the program starts
    loadfile(&head, DEFAULT_FILE);
    displaystudent(head);

    while (1){
        printf("\n Student Record Management System\n");
        printf("1. Add student\n");
        printf("2. Display Student\n");
        printf("3. Search Student by ID\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Save Data to File\n");
        printf("7. Load Data from File\n");
        printf("8. Sort the student record\n");
        printf("9. Check Statistics\n");
        printf("10. Search Student by Name\n");
        printf("11. Exit\n");

        int choice;
        if(scanf("%d", &choice) != 1){ clearbuffer(); printf("Invalid input.\n"); continue; }
        clearbuffer();

        switch (choice){
        case 1: {
            // now this one will be.... to.. add students
            int id, age;
            char name[50], department[50];
            float gpa;

            printf("Enter Student ID: ");
            if(scanf("%d", &id) != 1 || id <= 0){ clearbuffer(); printf("Invalid ID.\n"); break; }
            clearbuffer();

            readline("Enter Student Name: ", name, sizeof(name));

            printf("Enter Student age: ");
            if(scanf("%d", &age) != 1 || age <= 0 || age >= 120){ clearbuffer(); printf("Invalid age.\n"); break; }
            clearbuffer();

            readline("Enter Student Department: ", department, sizeof(department));

            printf("Enter Student GPA (0.0 - 4.0): ");
            if(scanf("%f", &gpa) != 1 || gpa < 0.0f || gpa > 4.0f){ clearbuffer(); printf("Invalid GPA.\n"); break; }
            clearbuffer();

            //now to to sent the info to the linked list, massa me am tired ya
            student* newstudent = createstudent(id, name, age, department, gpa);
            if(addstudent(&head, newstudent)){
                printf("\nsuccesfully added student to data database!\n");
                savedata(head, DEFAULT_FILE);
                displaystudent(head);// lemme just finish then we check and debug the code 1hr break abeg, i will be back bye
            }
            break;
        }
        case 2:
            // to display the student
            displaystudent(head);
            break;
        case 3: {
            // to search for a student by id
            int searchid;
            printf("Enter Student ID to search: ");
            if(scanf("%d", &searchid) != 1){ clearbuffer(); printf("Invalid ID.\n"); break; }
            clearbuffer();
            student* foundstudent = searchstudent(head, searchid);
            if(foundstudent != NULL){
                printf("Student found:\n");
                printf("\n  +--------+----------------------+-----+----------------------+-------+\n");
                printf("  | %-6s | %-20s | %-3s | %-20s | %-5s |\n", "ID", "Name", "Age", "Department", "GPA");
                printf("  +--------+----------------------+-----+----------------------+-------+\n");
                printf("  | %-6d | %-20s | %-3d | %-20s | %-5.2f |\n", foundstudent->id, foundstudent->name, foundstudent->age, foundstudent->department, foundstudent->gpa);
                printf("  +--------+----------------------+-----+----------------------+-------+\n");
            }else{
                printf("Student not found.\n");
            }
            break;
        }
            //am so sorry you'll
        case 4: {
            // to update a student by id
            int updateid;
            char newname[50], newdepartment[50];
            int newage;
            float Newgpa;

            printf("Enter Student ID to update: ");
            if(scanf("%d", &updateid) != 1){ clearbuffer(); printf("Invalid ID.\n"); break; }
            clearbuffer();

            if(searchstudent(head, updateid) == NULL){ printf("Student with ID %d not found.\n", updateid); break; }

            readline("Enter new Student Name: ", newname, sizeof(newname));

            printf("Enter new Student age: ");
            if(scanf("%d", &newage) != 1 || newage <= 0 || newage >= 120){ clearbuffer(); printf("Invalid age.\n"); break; }
            clearbuffer();

            readline("Enter new Student Department: ", newdepartment, sizeof(newdepartment));

            printf("Enter new Student GPA (0.0 - 4.0): ");
            if(scanf("%f", &Newgpa) != 1 || Newgpa < 0.0f || Newgpa > 4.0f){ clearbuffer(); printf("Invalid GPA.\n"); break; }
            clearbuffer();

            updatestudent(&head, updateid, newname, newage, newdepartment, Newgpa);
            savedata(head, DEFAULT_FILE);
            displaystudent(head);
            break;
        }
        case 5: {
            // and this one is to delete a student by id
            int deleteid;
            printf("Enter Student ID to delete: ");
            if(scanf("%d", &deleteid) != 1){ clearbuffer(); printf("Invalid ID.\n"); break; }
            clearbuffer();
            deletestudent(&head, deleteid);
            //AI is scary
            savedata(head, DEFAULT_FILE);
            displaystudent(head);
            break;
        }
        case 6: {
            char filename[50];
            printf("Enter a file name to save: ");
            scanf("%s", filename);
            clearbuffer();
            savedata(head, filename);
            printf("Student records successfully saved to file.\n");
            break;
        }
        case 7: {
            char loadfilename[50];
            printf("Enter a file name to load: ");
            scanf("%s", loadfilename);
            clearbuffer();
            loadfile(&head, loadfilename);
            printf("Student records successfully loaded from file.\n");
            displaystudent(head);
            break;
        }
        case 8:
            sortrecord(head);
            printf("Student records successfully sorted by ID.\n");
            savedata(head, DEFAULT_FILE);
            displaystudent(head);
            break;
        case 9:
            checkstatistics(head);
            break;
        case 10: {
            char searchname[50];
            readline("Enter Student Name to search: ", searchname, sizeof(searchname));
            student* foundstudent = searchstudentbyname(head, searchname);
            if(foundstudent != NULL){
                printf("Student found:\n");
                printf("\n  +--------+----------------------+-----+----------------------+-------+\n");
                printf("  | %-6s | %-20s | %-3s | %-20s | %-5s |\n", "ID", "Name", "Age", "Department", "GPA");
                printf("  +--------+----------------------+-----+----------------------+-------+\n");
                printf("  | %-6d | %-20s | %-3d | %-20s | %-5.2f |\n", foundstudent->id, foundstudent->name, foundstudent->age, foundstudent->department, foundstudent->gpa);
                printf("  +--------+----------------------+-----+----------------------+-------+\n");
            }else{
                printf("Student not found.\n");
            }
            break;
        }
        case 11:
            // to exit the program
            savedata(head, DEFAULT_FILE);
            freelist(&head); // free all memory before exit
            printf("Exiting the program. Goodbye!\n");
            return 0;
            
        
        default:
            //sorry my data is on so the ai will assist me in writing the code (lol)
            printf("Invalid choice, please try again.\n");
            break;
        }
    }
    
    return 0;
}