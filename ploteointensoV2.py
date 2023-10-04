import matplotlib.pyplot as plt
import pandas as pd
import time

# Lee el archivo de texto en un DataFrame de pandas
df = pd.read_csv('data.txt')

# Obtiene las columnas de datos
columnas = df.columns

# Recorre las columnas y crea una ventana para cada una
for col in columnas:
    plt.figure(figsize=(10, 6))  # Tamaño del gráfico

    # Recorre las filas y agrega datos dinámicamente
    for i in range(len(df)):
        plt.plot(df[col][:i + 1], label=col, marker='o', linestyle='-')

        # Configuración del gráfico
        plt.title('Gráficos')
        plt.xlabel('Índice')
        plt.ylabel('Valores')
        #plt.legend()  # Muestra las leyendas
        plt.grid(True)  # Muestra una cuadrícula en el gráfico

        # Muestra la ventana actual
        plt.pause(0.5)  # Espera 0.5 segundo antes de pasar al siguiente conjunto de datos
        plt.draw()  # Actualiza el gráfico actual

# Esto mantiene las ventanas de gráfico abiertas hasta que las cierres
plt.show()
