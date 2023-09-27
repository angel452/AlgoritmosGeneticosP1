import matplotlib.pyplot as plt
import numpy as np
import time

timeDelay = 0.3;

# Crear una figura con tres subplots para suma, media y máximo
fig, axs = plt.subplots(3, 1, figsize=(8, 10))

# Inicializar listas vacías para los datos de suma, media y máximo
suma_data = []
media_data = []
maximo_data = []

# Configurar los subplots
axs[0].set_title('Suma')
axs[1].set_title('Media')
axs[2].set_title('Máximo')

# Crear las líneas iniciales en los gráficos
linea_suma, = axs[0].plot([], [], lw=2)
linea_media, = axs[1].plot([], [], lw=2)
linea_maximo, = axs[2].plot([], [], lw=2)

# Función para actualizar los datos y los gráficos
def actualizar_graficos(epoca, suma, media, maximo):
    suma_data.append(suma)
    media_data.append(media)
    maximo_data.append(maximo)

    # Actualizar los datos de las líneas
    linea_suma.set_data(range(epoca + 1), suma_data)
    linea_media.set_data(range(epoca + 1), media_data)
    linea_maximo.set_data(range(epoca + 1), maximo_data)

    # Actualizar los límites de los ejes x e y para ajustarse a los nuevos datos
    for ax in axs:
        ax.relim()
        ax.autoscale_view()

    # Actualizar la figura
    plt.pause(timeDelay)  # Pausa de 1 segundo para visualización

# Simular datos de épocas
for epoca in range(10):
    suma = np.random.randint(500, 1500)
    media = np.random.randint(100, 500)
    maximo = np.random.randint(400, 800)

    actualizar_graficos(epoca, suma, media, maximo)
    time.sleep(timeDelay)  # Simular una época por segundo

# Mostrar los gráficos
plt.show()
