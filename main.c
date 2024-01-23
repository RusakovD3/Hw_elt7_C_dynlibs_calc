#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {
    void *lib_handle;
    int (*operation)(int, int);
    char choice;
    int a, b;

    printf("Enter two numbers: ");
    if(scanf("%d %d", &a, &b) != 2) {
        printf("Invalid input. Exiting.\n");
        exit(1);
    }
    
    while (1) {
        printf("Select the operation (+, -, *, /) Or q to quit Or c to change nums: ");
        if(scanf(" %c", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            exit(1);
        }

        switch (choice) {
            case '+':
                lib_handle = dlopen("./calk_dyn_libs/libadd.so", RTLD_LAZY);
                break;
            case '-':
                lib_handle = dlopen("./calk_dyn_libs/libsub.so", RTLD_LAZY);
                break;
            case '*':
                lib_handle = dlopen("./calk_dyn_libs/libmul.so", RTLD_LAZY);
                break;
            case '/':
                lib_handle = dlopen("./calk_dyn_libs/libdiv.so", RTLD_LAZY);
                break;
            case 'c':
                printf("Enter two numbers: ");
                if(scanf("%d %d", &a, &b) != 2) {
                    printf("Invalid input. Exiting.\n");
                    dlclose(lib_handle);
                    exit(1);
                }
                break;
            case 'q':
                printf("Quit.\n");
                dlclose(lib_handle);
                exit(0);
                break;
            default:
                printf("Invalid operation.\n");
                continue;
        }

        if (!lib_handle) {
            fprintf(stderr, "%s\n", dlerror());
            exit(1);
        }

        operation = dlsym(lib_handle, "add");
        if (choice == '-') {
            operation = dlsym(lib_handle, "sub");
        } else if (choice == '*') {
            operation = dlsym(lib_handle, "mul");
        } else if (choice == '/') {
            operation = dlsym(lib_handle, "div");
        }

        if (operation) {
            printf("Result: %d\n", operation(a, b));
        } else {
            fprintf(stderr, "%s\n", dlerror());
        }
    }

    return 0;
}
