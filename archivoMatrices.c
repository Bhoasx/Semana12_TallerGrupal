#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_ORDERS 100

// Estructuras para productos y órdenes de trabajo
typedef struct {
    char nombre[50];
    int cantidad;
    float precio;
} Producto;

typedef struct {
    char nombreProducto[50];
    int cantidadRequerida;
    int posible;
} OrdenTrabajo;

Producto productos[MAX_PRODUCTS];
OrdenTrabajo ordenes[MAX_ORDERS];
int totalProductos = 0;
int totalOrdenes = 0;

// Manejo de archivos
void guardarArchivoProductos() {
    FILE *archivo = fopen("productos.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de productos.\n");
        return;
    }
    for (int i = 0; i < totalProductos; i++) {
        fprintf(archivo, "%s %d %.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
    }
    fclose(archivo);
    printf("Productos guardados correctamente.\n");
}

void guardarArchivoOrdenes() {
    FILE *archivo = fopen("ordenes.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de órdenes.\n");
        return;
    }
    for (int i = 0; i < totalOrdenes; i++) {
        fprintf(archivo, "%s %d %d\n", ordenes[i].nombreProducto, ordenes[i].cantidadRequerida, ordenes[i].posible);
    }
    fclose(archivo);
    printf("Órdenes guardadas correctamente.\n");
}

void cargarArchivoProductos() {
    FILE *archivo = fopen("productos.txt", "r");
    if (archivo == NULL) {
        return;
    }
    while (fscanf(archivo, "%s %d %f", productos[totalProductos].nombre, &productos[totalProductos].cantidad, &productos[totalProductos].precio) != EOF) {
        totalProductos++;
    }
    fclose(archivo);
}

void cargarArchivoOrdenes() {
    FILE *archivo = fopen("ordenes.txt", "r");
    if (archivo == NULL) {
        return;
    }
    while (fscanf(archivo, "%s %d %d", ordenes[totalOrdenes].nombreProducto, &ordenes[totalOrdenes].cantidadRequerida, &ordenes[totalOrdenes].posible) != EOF) {
        totalOrdenes++;
    }
    fclose(archivo);
}

// Funciones de manipulación
void agregarProducto() {
    if (totalProductos < MAX_PRODUCTS) {
        printf("Ingrese nombre del producto: ");
        scanf("%s", productos[totalProductos].nombre);
        printf("Ingrese cantidad: ");
        scanf("%d", &productos[totalProductos].cantidad);
        printf("Ingrese precio: ");
        scanf("%f", &productos[totalProductos].precio);
        totalProductos++;
        printf("Producto agregado exitosamente.\n");
    } else {
        printf("No se pueden agregar más productos.\n");
    }
}

void editarProducto() {
    char nombreBusqueda[50];
    printf("Ingrese nombre del producto a editar: ");
    scanf("%s", nombreBusqueda);
    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productos[i].nombre, nombreBusqueda) == 0) {
            printf("Ingrese nueva cantidad: ");
            scanf("%d", &productos[i].cantidad);
            printf("Ingrese nuevo precio: ");
            scanf("%f", &productos[i].precio);
            printf("Producto editado correctamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void eliminarProducto() {
    char nombreEliminar[50];
    printf("Ingrese nombre del producto a eliminar: ");
    scanf("%s", nombreEliminar);
    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productos[i].nombre, nombreEliminar) == 0) {
            for (int j = i; j < totalProductos - 1; j++) {
                productos[j] = productos[j + 1];
            }
            totalProductos--;
            printf("Producto eliminado exitosamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void consultarProducto() {
    char nombreBusqueda[50];
    printf("Ingrese nombre del producto a buscar: ");
    scanf("%s", nombreBusqueda);
    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productos[i].nombre, nombreBusqueda) == 0) {
            printf("Producto encontrado: %s - Cantidad: %d - Precio: %.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void mostrarProductos() {
    for (int i = 0; i < totalProductos; i++) {
        printf("%s - Cantidad: %d - Precio: %.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
    }
}

void ingresarOrdenTrabajo() {
    char nombreProducto[50];
    int cantidadRequerida;
    printf("Ingrese nombre del producto: ");
    scanf("%s", nombreProducto);
    printf("Ingrese cantidad requerida: ");
    scanf("%d", &cantidadRequerida);

    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productos[i].nombre, nombreProducto) == 0) {
            ordenes[totalOrdenes].posible = (productos[i].cantidad >= cantidadRequerida) ? 1 : 0;
            if (ordenes[totalOrdenes].posible) {
                productos[i].cantidad -= cantidadRequerida;
                printf("Orden posible, cantidad actualizada.\n");
            } else {
                printf("No hay suficiente stock para esta orden.\n");
            }
            strcpy(ordenes[totalOrdenes].nombreProducto, nombreProducto);
            ordenes[totalOrdenes].cantidadRequerida = cantidadRequerida;
            totalOrdenes++;
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void mostrarOrdenesTrabajo() {
    for (int i = 0; i < totalOrdenes; i++) {
        printf("Orden: %s - Cantidad: %d - Posible: %s\n", ordenes[i].nombreProducto, ordenes[i].cantidadRequerida, ordenes[i].posible ? "Si" : "No");
    }
}

void buscarOrdenTrabajo() {
    char nombreBusqueda[50];
    printf("Ingrese nombre del producto en la orden: ");
    scanf("%s", nombreBusqueda);
    for (int i = 0; i < totalOrdenes; i++) {
        if (strcmp(ordenes[i].nombreProducto, nombreBusqueda) == 0) {
            printf("Orden encontrada: %s - Cantidad: %d - Posible: %s\n", ordenes[i].nombreProducto, ordenes[i].cantidadRequerida, ordenes[i].posible ? "Si" : "No");
            return;
        }
    }
    printf("Orden no encontrada.\n");
}

int main() {
    int opcion;
    cargarArchivoProductos();
    cargarArchivoOrdenes();

    do {
        printf("\nMENU:\n");
        printf("1. Agregar Producto\n");
        printf("2. Editar Producto\n");
        printf("3. Eliminar Producto\n");
        printf("4. Consultar Producto\n");
        printf("5. Mostrar Todos los Productos\n");
        printf("6. Ingresar Orden de Trabajo\n");
        printf("7. Mostrar Ordenes de Trabajo\n");
        printf("8. Buscar Orden de Trabajo\n");
        printf("9. Guardar Archivos\n");
        printf("10. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                editarProducto();
                break;
            case 3:
                eliminarProducto();
                break;
            case 4:
                consultarProducto();
                break;
            case 5:
                mostrarProductos();
                break;
            case 6:
                ingresarOrdenTrabajo();
                break;
            case 7:
                mostrarOrdenesTrabajo();
                break;
            case 8:
                buscarOrdenTrabajo();
                break;
            case 9:
                guardarArchivoProductos();
                guardarArchivoOrdenes();
                break;
            case 10:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 10);

    return 0;
}
