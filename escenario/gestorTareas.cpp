#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Tarea
{
private:
    string nombre;
    string curso;
    string fechaInicio;
    string fechaFin;
    string completada;

public:
    Tarea(const string &nombre, const string &curso, const string &fechaInicio, const string &fechaFin)
        : nombre(nombre), curso(curso), fechaInicio(fechaInicio), fechaFin(fechaFin), completada("Pendiente") {}
    const string &obtenerNombre() const
    {
        return nombre;
    }
    const string &obtenerCurso() const
    {
        return curso;
    }
    const string &obtenerFechaInicio() const
    {
        return fechaInicio;
    }
    const string &obtenerFechaFin() const
    {
        return fechaFin;
    }
    const string &obtenerCompletada() const
    {
        return completada;
    }
    void marcarComoCompletada()
    {
        completada = "Completada";
    }
};

class GestorTareas
{
private:
    vector<Tarea> tareas;
public:
    void crearTarea(const string &nombreTarea, const string &curso, const string &fechaInicio, const string &fechaFin)
    {
        tareas.emplace_back(nombreTarea, curso, fechaInicio, fechaFin);
        cout << "Tarea '" << nombreTarea << "' creada correctamente." << endl;
    }
    void eliminarTarea(const string &nombreTarea)
    {
        auto it = find_if(tareas.begin(), tareas.end(), [&nombreTarea](const Tarea &tarea)
                          { return tarea.obtenerNombre() == nombreTarea; });

        if (it != tareas.end()){
            tareas.erase(it);
            cout << "Tarea '" << nombreTarea << "' eliminada correctamente." << endl;
        }
        else{
            cout << "La tarea '" << nombreTarea << "' no fue encontrada." << endl;
        }
    }
    void marcarTareaComoCompletada(const string &nombreTarea)
    {
        auto it = find_if(tareas.begin(), tareas.end(), [&nombreTarea](const Tarea &tarea)
                          { return tarea.obtenerNombre() == nombreTarea; });

        if (it != tareas.end()){
            it->marcarComoCompletada();
            cout << "Tarea '" << nombreTarea << "' marcada como completada." << endl;
        }
        else{
            cout << "La tarea '" << nombreTarea << "' no fue encontrada." << endl;
        }
    }
    const vector<Tarea> &obtenerTareas() const{
        return tareas;
    }
};

class GestorPresentacionTareas
{
public:
    virtual void mostrarTareas(const vector<Tarea> &tareas) const = 0;
    virtual ~GestorPresentacionTareas() {}
};

class PresentadorConsola : public GestorPresentacionTareas
{
public:
    void mostrarTareas(const vector<Tarea> &tareas) const override
    {
        cout << "Tareas:" << endl;
        for (const auto &tarea : tareas)
        {
            cout << "Nombre: " << tarea.obtenerNombre() << endl;
            cout << "Curso: " << tarea.obtenerCurso() << endl;
            cout << "Fecha de inicio: " << tarea.obtenerFechaInicio() << endl;
            cout << "Fecha de fin: " << tarea.obtenerFechaFin() << endl;
            cout << "Completada: " << tarea.obtenerCompletada() << endl;
            cout << endl;
        }
    }
};

int main()
{
    GestorTareas gestor;
    PresentadorConsola presentador;
    int opcion;

    do
    {
        cout << "---- Menú ----" << endl;
        cout << "1. Crear tarea" << endl;
        cout << "2. Marcar tarea como completada" << endl;
        cout << "3. Eliminar tarea" << endl;
        cout << "4. Mostrar tareas" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            string nombreTarea, curso, fechaInicio, fechaFin;
            int diaI, mesI, anioI, diaF, mesF, anioF;

            cout << "Ingrese el nombre de la tarea: ";
            cin >> nombreTarea;

            cout << "Ingrese el nombre del curso: ";
            cin >> curso;

            // Ingresar la fecha de inicio
            cout << "Ingrese la fecha de inicio (DD/MM/AAAA): ";
            do
            {
                cout << "Ingrese dia valido: ";
                cin >> diaI;
            } while (diaI < 1 or diaI > 31);
            do
            {
                cout << "Ingrese mes valido: ";
                cin >> mesI;
            } while (mesI < 1 or mesI > 12);
            do
            {
                cout << "Ingrese anio valido: ";
                cin >> anioI;
            } while (to_string(anioI).size() != 4);
            fechaInicio = to_string(diaI) + "/" + to_string(mesI) + "/" + to_string(anioI);

            // Ingresar la fecha de fin
            cout << "Ingrese la fecha de fin (DD/MM/AAAA): ";
            do
            {
                cout << "Ingrese dia valido: ";
                cin >> diaF;
            } while (diaF < 1 or diaF > 31);
            do
            {
                cout << "Ingrese mes valido: ";
                cin >> mesF;
            } while (mesF < 1 or mesF > 12);
            do
            {
                cout << "Ingrese anio valido: ";
                cin >> anioF;
            } while (to_string(anioF).size() != 4);
            fechaFin = to_string(diaF) + "/" + to_string(mesF) + "/" + to_string(anioF);

            cout << "Tarea '" << nombreTarea << "' creada correctamente." << endl;
            cout << "Curso: " << curso << endl;
            cout << "Fecha de inicio: " << fechaInicio << endl;
            cout << "Fecha de fin: " << fechaFin << endl;

            gestor.crearTarea(nombreTarea, curso, fechaInicio, fechaFin);
            break;
        }
        case 2:
        {
            string nombreTarea;
            cout << "Ingrese el nombre de la tarea a marcar como completada: ";
            cin >> nombreTarea;
            gestor.marcarTareaComoCompletada(nombreTarea);
            break;
        }
        case 3:
        {
            string nombreTarea;
            cout << "Ingrese el nombre de la tarea a eliminar: ";
            cin >> nombreTarea;
            gestor.eliminarTarea(nombreTarea);
            break;
        }
        case 4:
            presentador.mostrarTareas(gestor.obtenerTareas());
            break;
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
        }
    } while (opcion != 5);

    return 0;
}
