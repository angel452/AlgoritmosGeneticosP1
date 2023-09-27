#include <matplotlibcpp.h>
#include <vector>
#include <random>
#include <thread> // Para sleep

namespace plt = matplotlibcpp;

const double timeDelay = 0.3;

int main() {
    // Crear una figura con tres subplots para suma, media y máximo
    plt::figure_size(800, 600);
    std::vector<double> epocas;
    std::vector<double> suma_data;
    std::vector<double> media_data;
    std::vector<double> maximo_data;

    // Configurar los subplots
    plt::subplot(3, 1, 1);
    plt::title("Suma");
    plt::subplot(3, 1, 2);
    plt::title("Media");
    plt::subplot(3, 1, 3);
    plt::title("Máximo");

    // Función para actualizar los datos y los gráficos
    auto actualizar_graficos = [&](int epoca, double suma, double media, double maximo) {
        epocas.push_back(epoca);
        suma_data.push_back(suma);
        media_data.push_back(media);
        maximo_data.push_back(maximo);

        // Actualizar los datos de las líneas
        plt::subplot(3, 1, 1);
        plt::plot(epocas, suma_data);
        plt::subplot(3, 1, 2);
        plt::plot(epocas, media_data);
        plt::subplot(3, 1, 3);
        plt::plot(epocas, maximo_data);

        // Mostrar la figura actualizada
        plt::pause(timeDelay);
    };

    // Simular datos de épocas
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> suma_dist(500, 1500);
    std::uniform_int_distribution<int> media_dist(100, 500);
    std::uniform_int_distribution<int> maximo_dist(400, 800);

    for (int epoca = 0; epoca < 10; ++epoca) {
        double suma = suma_dist(gen);
        double media = media_dist(gen);
        double maximo = maximo_dist(gen);

        actualizar_graficos(epoca, suma, media, maximo);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(timeDelay * 1000)));
    }

    // Mostrar los gráficos
    plt::show();

    return 0;
}
