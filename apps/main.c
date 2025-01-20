#include <stdio.h>
#include <string.h>
#include "avl.h"
#include "heap.h"
#include "hash.h"

int main()
{
    NodeAVL *root_avl = NULL;
    NodeHeap *root_heap = NULL;

    FILE *file = fopen("./input/input-1.txt", "r");

    char line_file[100], line_name[20];
    int room_code, room_capacity, room_priority, new_priority;

    if (file == NULL)
    {
        perror("Error opening file.\n");
        return 0;
    }

    // Reading the input file
    while (fgets(line_file, sizeof(line_file), file) != NULL)
    {
        sscanf(line_file, "%s", line_name);

        if (strcmp(line_name, "CRIAR_SALA") == 0) {
            sscanf(line_file, "%*s %d %d", &room_code, &room_capacity);
            root_avl = insertRoom(root_avl, room_code, room_capacity); // Cria a sala na AVL
                                                                  // **Joga na hash como 'disponivel'  
        } else if (strcmp(line_name, "RESERVAR_SALA") == 0) {
            sscanf(line_file, "%*s %d %d", &room_code, &room_priority); 
            insert(&root_heap, room_code, room_priority);              // Cria a reserva no Heap
                                                                     // **Joga na hash como 'disponivel'  
            
        } else if (strcmp(line_name, "BLOQUEAR_SALA") == 0) {
            sscanf(line_file, "%*s %d", &room_code);                                                       // **Joga na hash como 'disponivel'  
                                                                    // **Joga na hash como 'ocupada'                                                         
        } else if (strcmp(line_name, "DESBLOQUEAR_SALA") == 0) {
            sscanf(line_file, "%*s %d", &room_code);                                                       // **Joga na hash como 'disponivel'  
                                                                   // **Joga na hash como 'disponivel' 
        } else if (strcmp(line_name, "CANCELAR_RESERVA") == 0) {
            sscanf(line_file, "%*s %d", &room_code);
            room_priority = findPriorityByCode(root_heap, room_code);            
            findAndRemoveByPriority(root_heap, room_priority);     // Removendo a reserva
            
            
        } else if (strcmp(line_name, "LISTAR_SALAS") == 0){
            puts("Available rooms:");                        // Listando as salas (AVL)
            showAVLTree(root_avl); 
            puts("");                                                     // **Joga na hash como 'disponivel'  

        } else if (strcmp(line_name, "CONSULTAR_SALA") == 0){
            sscanf(line_file, "%*s %d", &room_code); 
                                                                      // **Joga na hash como 'disponivel'  
                                                                // **Imprimir o estado da sala na hash
        } else if (strcmp(line_name, "ATUALIZAR_PRIORIDADE") == 0) {
            sscanf(line_file, "%*s %d %d", &room_code, &new_priority); 
            room_priority = findPriorityByCode(root_heap, room_code);
            findAndRemoveByPriority(root_heap, room_priority);   
            insert(&root_heap, room_code, new_priority);         // Substituindo a prioridade da reserva 
                                                                     // **Joga na hash como 'disponivel'  

        } else {
            perror("Problem reading the line...");
        }
    }
    // Closing the file
    fclose(file);

    puts("AVL (Rooms):");
    showAVLTree(root_avl);
    puts("");

    puts("HEAP (Reservations):");
    printInOrder(root_heap);

    return 0;
}