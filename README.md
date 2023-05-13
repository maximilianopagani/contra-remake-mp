# Contra Remake MP

Juego de plataformas con multijugador LAN tipo Contra (NES, 1987), desarrollado en el 2C de 2018 para la cátedra Azcurra de Taller de Programación, Facultad de Ingeniería, Universidad de Buenos Aires (UBA)

## Features

- Multijugador LAN
- Escenarios con efecto parallax
- 3 niveles distintos con scroll horizontal (2) y vertical (1)
- 2 tipos de enemigos comunes: estáticos y corredores
- 3 jefes finales, uno por nivel
- 4 tipos de armas
- Características configurables por archivo
  - Tipo y posición de plataformas
  - Tipo y cantidad de enemigos
  - Ruta para los fondos de escenario
  - Posición y tipo para spawn de armas

## Características técnicas

- Patrón MVC
- Arquitectura cliente-servidor
- C++
- SDL (gráficos y sonidos)
- Launcher por CLI
- Unix `<sys/socket>` UDP y `<thread>` para networking y multithreading

## Video preview

[![Watch the video](https://img.youtube.com/vi/ojdA1kXy-IA/maxresdefault.jpg)](https://youtu.be/ojdA1kXy-IA)
