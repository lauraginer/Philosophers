# 🍝 Philosophers

Una implementación en C del clásico problema de los filósofos comensales, que demuestra los conceptos de programación concurrente, sincronización de hilos y prevención de deadlocks.

## 📋 Descripción del Problema

El problema de los filósofos comensales es un problema clásico de ciencias de la computación que ilustra los desafíos de la sincronización en sistemas concurrentes:

- **N filósofos** se sientan alrededor de una mesa circular
- Cada filósofo alterna entre **pensar**, **comer** y **dormir**
- Para comer, un filósofo necesita **dos tenedores** (uno a cada lado)
- Solo hay **N tenedores** en total (uno entre cada par de filósofos)
- Los filósofos no pueden comunicarse entre sí

### 🎯 Objetivos
- Evitar **deadlocks** (todos los filósofos bloqueados esperando tenedores)
- Evitar **race conditions** (acceso concurrente a recursos compartidos)
- Garantizar que ningún filósofo muera de hambre
- Detectar la muerte de un filósofo con precisión (≤ 10ms de retraso)

## 🏗️ Arquitectura del Proyecto

```
philo/
├── Makefile              # Compilación y tareas automatizadas
├── inc/
│   └── philosopher.h     # Definiciones de estructuras y prototipos
└── src/
    ├── main.c           # Función principal y validación de argumentos
    ├── utils.c          # Funciones de utilidad (tiempo, conversiones)
    ├── mutex.c          # Gestión de mutexes
    ├── threads.c        # Creación y gestión de hilos
    ├── monitor.c        # Monitorización de estado y detección de muerte
    └── actions.c        # Acciones de los filósofos (comer, dormir, pensar)
```

## 🚀 Compilación y Uso

### Compilación
```bash
make                # Compilación estándar
make debug          # Compilación con símbolos de debug (-g)
make valgrind       # Compilación y ejecución con Valgrind
```

### Ejecución
```bash
./philo <num_philos> <time_die> <time_eat> <time_sleep> [num_meals]
```

#### Parámetros:
- `num_philos`: Número de filósofos (y tenedores)
- `time_die`: Tiempo en ms antes de que un filósofo muera sin comer
- `time_eat`: Tiempo en ms que tarda un filósofo en comer
- `time_sleep`: Tiempo en ms que tarda un filósofo en dormir
- `num_meals`: (Opcional) Número de comidas requeridas para terminar la simulación

#### Ejemplos:
```bash
./philo 4 410 200 200        # 4 filósofos, simulación infinita
./philo 5 800 200 200 7      # 5 filósofos, termina cuando todos coman 7 veces
./philo 2 310 200 200        # Caso crítico: probablemente algún filósofo muera
```

## 🧵 Implementación Técnica

### Estrategias de Sincronización

#### 1. **Prevención de Deadlocks**
- Los filósofos **pares** toman primero el tenedor derecho, luego el izquierdo
- Los filósofos **impares** toman primero el tenedor izquierdo, luego el derecho
- Esto rompe la condición de espera circular

#### 2. **Gestión de Mutexes**
```c
typedef struct s_data {
    pthread_mutex_t dead_mutex;    // Protege el flag de muerte
    pthread_mutex_t eat_mutex;     // Protege last_meal y num_meals
    pthread_mutex_t log;           // Serializa la salida por consola
    pthread_mutex_t *forks;        // Array de mutexes para tenedores
} t_data;
```

#### 3. **Detección Precisa de Muerte**
- Un hilo **monitor** separado verifica constantemente el estado de los filósofos
- Comprueba si `(tiempo_actual - ultima_comida) > tiempo_muerte`
- Garantiza detección en menos de 10ms

### Flujo de Ejecución

1. **Inicialización**: Validación de argumentos, creación de estructuras, inicialización de mutexes
2. **Creación de hilos**: Un hilo por filósofo + un hilo monitor
3. **Rutina del filósofo**: Bucle infinito de pensar → tomar tenedores → comer → soltar tenedores → dormir
4. **Monitorización**: Verificación continua de condiciones de muerte y finalización
5. **Finalización**: Limpieza de recursos y terminación controlada

## 🧪 Casos de Prueba

### Pruebas Básicas
```bash
./philo 1 800 200 200        # Un filósofo (debe morir)
./philo 4 410 200 200        # Caso estable
./philo 2 800 200 200        # Dos filósofos (alternancia perfecta)
```

### Pruebas de Precisión
```bash
./philo 2 310 200 200        # Muerte rápida: verificar retraso ≤ 10ms
./philo 4 310 200 200        # Muerte bajo presión
```

### Pruebas de Finalización
```bash
./philo 5 800 200 200 7      # Termina cuando todos coman 7 veces
./philo 3 800 200 200 1      # Termina rápidamente
```

### Herramientas de Debug y Análisis

#### Makefile Integrado
Mi Makefile incluye targets específicos para análisis:
```bash
make valgrind       # Ejecuta automáticamente con parámetros optimizados
# Equivale a: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./philo 4 410 200 200
```

#### Banner Personalizado
```
 ██████╗ ██╗  ██╗██╗██╗      ██████╗ 
 ██╔══██╗██║  ██║██║██║     ██╔═══██╗
 ██████╔╝███████║██║██║     ██║   ██║
 ██╔═══╝ ██╔══██║██║██║     ██║   ██║
 ██║     ██║  ██║██║███████╗╚██████╔╝
 ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ 
```

### Funciones de Error Personalizadas

#### `value_state_error()` - Debugging de Mutexes
```c
void value_state_error(int action);
```
Función específica que imprime mensajes de error descriptivos según la operación de mutex que falló:
- "Error: Failed to initialize mutex"
- "Error: Failed to lock mutex" 
- "Error: Failed to unlock mutex"
- "Error: Failed to destroy mutex"

### Helgrind (Detección de Race Conditions)
```bash
valgrind --tool=helgrind ./philo 4 410 200 200
```

### ThreadSanitizer (Compilación con TSan)
```bash
cc -fsanitize=thread -g src/*.c -o philo_tsan
./philo_tsan 4 410 200 200
```

## 📊 Formato de Salida

La simulación produce una salida con formato:
```
<timestamp_ms> <philosopher_id> <action>
```

Ejemplo:
```
0 1 is thinking
0 3 is thinking
1 1 has taken a fork
1 1 has taken a fork
1 1 is eating
201 1 is sleeping
201 2 has taken a fork
...
810 2 died
```

## 🎯 Características Destacadas de Mi Implementación

- ✅ **Thread-safe**: Uso correcto de mutexes para evitar race conditions
- ✅ **Deadlock-free**: Estrategia asimétrica de toma de tenedores
- ✅ **Detección precisa**: Monitor con precisión de ≤ 10ms usando `check_philo_death()`
- ✅ **Gestión de memoria**: Sin memory leaks con `free_arrays_and_destroy()`
- ✅ **Caso especial**: Manejo dedicado del filósofo único con `special_case()`
- ✅ **Terminación controlada**: Finalización cuando todos han comido suficiente
- ✅ **Wrapper de mutex**: Sistema unificado con `main_mutex()` y constantes `MTX_*`
- ✅ **Parsing robusto**: `convert_to_int()` personalizado con validación de overflow
- ✅ **Sleep preciso**: `time_to_sleep()` con busy waiting para mayor precisión temporal
- ✅ **Logging thread-safe**: `print_actions()` con doble verificación de estado
- ✅ **Código modular**: Funciones < 25 líneas cumpliendo Norminette
- ✅ **Verificación anticipada**: `is_dead()` antes de cada acción del filósofo

## 🛠️ Detalles de Implementación

### Gestión de Mutexes Personalizada

#### Función `main_mutex()` - Wrapper Unificado
```c
void main_mutex(pthread_mutex_t *mutex, int action);
```
Mi implementación utiliza una función centralizada que maneja todas las operaciones de mutex con constantes definidas:
- `MTX_INIT (0)`: Inicialización de mutex
- `MTX_LOCK (1)`: Bloqueo de mutex
- `MTX_UNLOCK (2)`: Desbloqueo de mutex  
- `MTX_DESTROY (3)`: Destrucción de mutex

Esta abstracción permite un control centralizado de errores y facilita el debugging.

#### Sistema de Mutexes Especializado
```c
typedef struct s_data {
    pthread_mutex_t dead_mutex;    // Control del flag de muerte global
    pthread_mutex_t done_mutex;    // Estado de finalización (no usado actualmente)
    pthread_mutex_t meal_mutex;    // Protege acceso a información de comidas
    pthread_mutex_t eat_mutex;     // Sincroniza last_meal y num_meals
    pthread_mutex_t log;           // Serializa toda la salida por consola
    pthread_mutex_t *forks;        // Array dinámico de tenedores
} t_data;
```

### Funciones Clave de Mi Implementación

#### `check_philo_death()` - Detección Modularizada
```c
int check_philo_death(t_data *data, int i, long long current_time);
```
Función extraída de `monitor_philo()` para cumplir con la Norminette (<25 líneas). 
- Retorna 1 si el filósofo ha muerto, 0 si sigue vivo
- Maneja internamente el bloqueo del `eat_mutex` y la escritura del mensaje de muerte

#### `dead_and_need_put_forks()` - Control de Estado
```c
static int dead_and_need_put_forks(t_philo *philo);
```
Función específica que verifica si un filósofo ha muerto después de tomar tenedores y los libera si es necesario. Evita deadlocks cuando un filósofo muere mientras tiene tenedores.

#### `special_case()` - Caso Único de Un Filósofo
```c
static int special_case(t_data *data);
```
Manejo específico del edge case con un solo filósofo:
- Toma un tenedor, espera `time_die` y muere
- Evita crear hilos innecesarios para este caso trivial

### Funciones de Utilidad Personalizadas

#### `convert_to_int()` - Parsing Robusto
Mi propia implementación de atoi que:
- Rechaza números negativos (retorna 0)
- Maneja overflow devolviendo `INT_MAX`
- Ignora espacios en blanco iniciales

#### `obtain_time()` - Timestamp Preciso
```c
long long obtain_time(void);
```
Obtiene timestamp en milisegundos usando `gettimeofday()`:
```c
return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
```

#### `time_to_sleep()` - Sleep Activo
```c
int time_to_sleep(long long duration);
```
Implementación de sleep preciso usando busy waiting con `usleep(100)`:
- Más preciso que `usleep(duration)` directo
- Balance entre precisión temporal y uso de CPU

### Sistema de Logging Thread-Safe

#### `print_actions()` - Salida Sincronizada
```c
void print_actions(t_data *data, int philo_id, char *log);
```
Características únicas:
- **Doble verificación**: Comprueba `data->dead` antes y después de adquirir el mutex de log
- **Timestamp relativo**: Calcula `current_time - data->init_time` para timestamps desde el inicio
- **Prevención de mensajes fantasma**: Evita imprimir acciones después de que alguien haya muerto

### Optimizaciones Específicas

#### Estrategia de Verificación Anticipada
En `routine_threads()`, verifico `is_dead()` antes de cada acción:
```c
if (is_dead(philo) == 1) return (NULL);  // Antes de pensar
if (is_dead(philo) == 1) return (NULL);  // Antes de tomar tenedores
// ... etc
```

#### `is_dead()` - Función Thread-Safe
```c
int is_dead(t_philo *philo);
```
Acceso seguro al flag global de muerte usando el `dead_mutex`, evitando lecturas inconsistentes.

### Gestión de Memoria y Limpieza

#### `free_arrays_and_destroy()` - Limpieza Completa
Mi función personalizada que:
- Libera arrays dinámicos (`philos`, `forks`)
- Destruye todos los mutexes de tenedores individualmente
- Destruye mutexes de control (`dead_mutex`, `done_mutex`)
- Establece punteros a NULL para evitar double-free

### Inicialización Robusta

#### `init_philo()` - Setup de Filósofos
Configuración detallada de cada filósofo:
- Asignación de tenedores con aritmética modular: `(i + 1) % args->num_philos`
- Inicialización de `last_meal` con timestamp actual
- Configuración de puntero a datos compartidos para cada filósofo

## 📚 Normas y Estándares

- **Norminette**: Código conforme al estándar de 42
- **No funciones prohibidas**: Solo funciones permitidas del subject
- **Sin variables globales**: Toda la información en estructuras locales
- **Gestión de errores**: Manejo robusto de fallos de sistema

---
**Autor**: Laura Giner  
**Fecha**: Septiembre 2025  
**Proyecto**: 42 School - Philosophers
