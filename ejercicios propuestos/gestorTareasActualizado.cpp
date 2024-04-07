#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Proyecto
{
private:
    string nombre;
    string descripcion;
    string fechaInicio;
    string fechaFin;
    string responsable;
    string estado;
    vector<string> comentarios;
    vector<string> archivos;

public:
    Proyecto() {}

    Proyecto(string nombre, string descripcion, string fechaInicio, string fechaFin, string responsable):nombre(nombre),descripcion(descripcion),
        fechaInicio(fechaInicio),
        fechaFin(fechaFin),
        responsable(responsable),
        estado("Pendiente"),
        comentarios({}),
        archivos({})
    {};

    string getNombre() const { return nombre; }
    string getDescripcion() const { return descripcion; }
    string getFechaInicio() const { return fechaInicio; }
    string getFechaFin() const { return fechaFin; }
    string getResponsable() const { return responsable; }
    string getEstado() const { return estado; }
    vector<string> getComentarios() const { return comentarios; }
    vector<string> getArchivos() const { return archivos; }


    void setNombre(const string &nuevoNombre) { nombre = nuevoNombre; }
    void setDescripcion(const string &nuevaDescripcion) { descripcion = nuevaDescripcion; }
    void setFechaInicio(const string &nuevaFechaInicio) { fechaInicio = nuevaFechaInicio; }
    void setFechaFin(const string &nuevaFechaFin) { fechaFin = nuevaFechaFin; }
    void setResponsable(const string &nuevoResponsable) { responsable = nuevoResponsable; }
    void setEstado(const string &nuevoEstado) { estado = nuevoEstado; }
    void setComentarios(const vector<string> &comentariosActualizados) { comentarios = comentariosActualizados; }
    void setArchivos(const vector<string> &archivosActualizados) { archivos = archivosActualizados; }
};

class GestorProyectos
{
private:
    vector<Proyecto> proyectos;
    vector<string> archivosCompartidos;

public:
    const vector<string> getArchivos(){
        return archivosCompartidos;
    }
    const vector<Proyecto> &obtenerProyectos() const{
        return proyectos;
    }

    void crearProyecto(string &nombreProyecto, string &descripcion, string &fechaInicio, string &fechaFin, string &responsable){
        proyectos.emplace_back(nombreProyecto, descripcion, fechaInicio, fechaFin, responsable);
        cout << "Proyecto '" << nombreProyecto << "' creada correctamente." << endl;
    }
    void eliminarProyecto(const string &nombreProyecto){
        auto it = find_if(proyectos.begin(), proyectos.end(), [&nombreProyecto](const Proyecto &proyecto)
                          { return proyecto.getNombre() == nombreProyecto; });

        if (it != proyectos.end()){
            proyectos.erase(it);
            cout << "Proyecto '" << nombreProyecto << "' eliminada correctamente." << endl;
        }
        else{
            cout << "La proyecto '" << nombreProyecto << "' no fue encontrada." << endl;
        }
    }
    void marcarProyectoComoCompletada(const string &nombreProyecto){
        auto it = find_if(proyectos.begin(), proyectos.end(), [&nombreProyecto](const Proyecto &proyecto)
                          { return proyecto.getNombre() == nombreProyecto; });

        if (it != proyectos.end()){
            it->setEstado("Completado");
            cout << "Proyecto '" << nombreProyecto << "' marcada como completada." << endl;
        }
        else{
            cout << "La proyecto '" << nombreProyecto << "' no fue encontrada." << endl;
        }
    }
    void AgregarComentario(const string nombreProyecto, const string &comentario){
        auto it = find_if(proyectos.begin(), proyectos.end(), [&nombreProyecto](const Proyecto &proyecto)
                          { return proyecto.getNombre() == nombreProyecto; });

        if (it != proyectos.end()){
            vector<string> comentarios = it->getComentarios();
            comentarios.push_back(comentario); // Corrección: se agregó el comentario al vector
            it->setComentarios(comentarios);
            cout << "Comentario agregado al proyecto '" << nombreProyecto << "'." << endl;
        }
        else{
            cout << "El proyecto '" << nombreProyecto << "' no fue encontrado." << endl;
        }
    }
    void agregarArchivo(const string nombreProyecto, const string &archivo){
        archivosCompartidos.push_back(archivo);
        auto it = find_if(proyectos.begin(), proyectos.end(), [&nombreProyecto](const Proyecto &proyecto)
                          { return proyecto.getNombre() == nombreProyecto; });

        if (it != proyectos.end()){
            vector<string> archivos = it->getArchivos();
            archivos.push_back(archivo); // Corrección: se agregó el comentario al vector
            it->setArchivos(archivos);
            cout << "Archivo agregado al proyecto '" << nombreProyecto << "'." << endl;
        }
        else{
            cout << "El proyecto '" << nombreProyecto << "' no fue encontrado." << endl;
        }
    }
};

class GestorPresentacionProyectos{
public:
    virtual void mostrarProyectos(const vector<Proyecto> &proyectos) const = 0;
    virtual ~GestorPresentacionProyectos() {}
};

class PresentadorConsolaProyectos : public GestorPresentacionProyectos{
public:
    void mostrarProyectos(const vector<Proyecto> &proyectos) const{
        cout << "Proyectos:" << endl;
        for (const auto &proyecto : proyectos){
            cout << "Nombre: " << proyecto.getNombre() << endl;
            cout << "Descripción: " << proyecto.getDescripcion() << endl;
            cout << "Fecha de inicio: " << proyecto.getFechaInicio() << endl;
            cout << "Fecha de fin: " << proyecto.getFechaFin() << endl;
            cout << "Responsable: " << proyecto.getResponsable() << endl;
            cout << "Estado: " << proyecto.getEstado() << endl;
            cout << "Comentarios: " << endl;
            for (const auto &comentario : proyecto.getComentarios())
            {
                cout << comentario << endl;
            }
            cout << "Archivos: " << endl;
            for (const auto &archivo : proyecto.getArchivos())
            {
                cout << archivo << endl;
            }

            cout << endl;
        }

    }
};

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

        if (it != tareas.end())
        {
            tareas.erase(it);
            cout << "Tarea '" << nombreTarea << "' eliminada correctamente." << endl;
        }
        else
        {
            cout << "La tarea '" << nombreTarea << "' no fue encontrada." << endl;
        }
    }
    void marcarTareaComoCompletada(const string &nombreTarea)
    {
        auto it = find_if(tareas.begin(), tareas.end(), [&nombreTarea](const Tarea &tarea)
                          { return tarea.obtenerNombre() == nombreTarea; });

        if (it != tareas.end())
        {
            it->marcarComoCompletada();
            cout << "Tarea '" << nombreTarea << "' marcada como completada." << endl;
        }
        else
        {
            cout << "La tarea '" << nombreTarea << "' no fue encontrada." << endl;
        }
    }
    const vector<Tarea> &obtenerTareas() const
    {
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

void mostrarMenuTareas()
{
    cout << "---- Menú de Tareas ----" << endl;
    cout << "1. Crear tarea" << endl;
    cout << "2. Marcar tarea como completada" << endl;
    cout << "3. Eliminar tarea" << endl;
    cout << "4. Mostrar tareas" << endl;
    cout << "5. Salir" << endl;
}

void mostrarMenuProyectos()
{
    cout << "---- Menú de Proyectos ----" << endl;
    cout << "1. Crear proyecto" << endl;
    cout << "2. Marcar proyecto como completado" << endl;
    cout << "3. Eliminar proyecto" << endl;
    cout << "4. Comentar proyecto" << endl;
    cout << "5. Compartir archivos" << endl;
    cout << "6. Mostrar proyectos y archivos compartidos" << endl;
    cout << "7. Salir" << endl;
}

int main()
{
    int opcion;
    bool salir = false;
    GestorProyectos gestorProyectos;
    GestorTareas gestorTareas;
    PresentadorConsola presentadorTareas;
    PresentadorConsolaProyectos presentadorProyectos;
    do
    {
        cout << "Seleccione el tipo de gestión:" << endl;
        cout << "1. Tareas" << endl;
        cout << "2. Proyectos" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            do
            {
                mostrarMenuTareas();
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

                    gestorTareas.crearTarea(nombreTarea, curso, fechaInicio, fechaFin);
                    break;
                }
                case 2:
                {
                    string nombreTarea;
                    cout << "Ingrese el nombre de la tarea a marcar como completada: ";
                    cin >> nombreTarea;
                    gestorTareas.marcarTareaComoCompletada(nombreTarea);
                    break;
                }
                case 3:
                {
                    string nombreTarea;
                    cout << "Ingrese el nombre de la tarea a eliminar: ";
                    cin >> nombreTarea;
                    gestorTareas.eliminarTarea(nombreTarea);
                    break;
                }
                case 4:
                {
                    presentadorTareas.mostrarTareas(gestorTareas.obtenerTareas());
                    break;
                }
                case 5:
                {
                    cout << "Saliendo del menú de tareas..." << endl;
                    salir = true;
                    break;
                }

                default:
                    cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
                }
            } while (!salir);
            salir = false; // Reiniciar la bandera para el próximo ciclo
            break;
        case 2:
            do
            {
                mostrarMenuProyectos();
                cout << "Ingrese una opción: ";
                cin >> opcion;

                switch (opcion)
                {
                case 1:
                {
                    string nombreProyecto, descripcion, fechaInicio, fechaFin, responsable;
                    int diaI, mesI, anioI, diaF, mesF, anioF;

                    cout << "Ingrese el nombre de proyecto: ";
                    cin >> nombreProyecto;

                    cout << "Ingrese la descripcion del proyecto: ";
                    cin >> descripcion;

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
                    
                    cout << "Ingrese el nombre del responsable del proyecto: ";
                    cin >> responsable;

                    cout << "Proyecto '" << nombreProyecto << "' creada correctamente." << endl;
                    cout << "Descripcion: " << descripcion << endl;
                    cout << "Fecha de inicio: " << fechaInicio << endl;
                    cout << "Fecha de fin: " << fechaFin << endl;

                    gestorProyectos.crearProyecto(nombreProyecto, descripcion, fechaInicio, fechaFin, responsable);
                    break;
                }
                case 2:
                {
                    string nombreProyecto;
                    cout << "Ingrese el nombre del proyecto a marcar como completada: ";
                    cin >> nombreProyecto;
                    gestorProyectos.marcarProyectoComoCompletada(nombreProyecto);
                    break;
                }
                case 3:
                {
                    string nombreProyecto;
                    cout << "Ingrese el nombre del proyecto a eliminar: ";
                    cin >> nombreProyecto;
                    gestorTareas.eliminarTarea(nombreProyecto);
                    break;
                }
                case 4:
                {
                    string nombreProyecto;
                    string comentario;
                    cout << "Ingrese el nombre del proyecto que quiere comentar" << endl;
                    cin >> nombreProyecto;
                    cout << "Ingrese el comentario" << endl;
                    cin >> comentario;
                    gestorProyectos.AgregarComentario(nombreProyecto, comentario);
                    break;
                }
                case 5:
                {
                    string nombreProyecto;
                    string archivo;
                    cout << "Ingrese el nombre del proyecto que quiere comentar" << endl;
                    cin >> nombreProyecto;
                    cout << "Ingrese la ruta del archivo" << endl;
                    cin >> archivo;
                    gestorProyectos.agregarArchivo(nombreProyecto,archivo);
                    break;
                }
                case 6:
                {
                    presentadorProyectos.mostrarProyectos(gestorProyectos.obtenerProyectos());
                    break;
                }
                case 7:
                {
                    cout << "Saliendo del menú de proyectos..." << endl;
                    salir = true;
                    break;
                }
                default:
                    cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
                }
            } while (!salir);
            salir = false;
            break;
        case 3:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
        }
    } while (opcion != 3);

    return 0;
}
