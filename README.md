# Euclid ICU Boot Software (BSW)

Boot Software (BSW) para la **Instrument Control Unit (ICU)**, orientado a *power-on initialization*, verificación básica de memoria y arranque seguro del sistema. Proyecto en **C** para **Cortex-M3**, desarrollado con **SEGGER Embedded Studio** y organizado por capas (Setup/System/Source).

> Este repositorio muestra la **arquitectura y el enfoque** del BSW a nivel académico/pedagógico. No contiene información sensible ni datos protegidos.

---

## Objetivos del BSW

- **Inicialización temprana** de reloj, memoria y periféricos mínimos.
- **Chequeos de integridad** (CRC16/EDAC) sobre regiones críticas.
- **Gestión de arranque**: selección de imagen válida, fallback seguro si falla la primaria.
- **Hook** para recibir **telecomandos** de prueba (stub) y exponer *health status*.

---

## Estructura
```text
euclid-icu-boot/
├─ Setup/ # Scripts, configuraciones y linker (si aplica)
├─ System/ # Abstracciones de sistema / BSP / RTOS hooks
├─ Source/ # Código de aplicación boot + drivers (uart, flash, gpio)
├─ project.emProject
└─ project.emSession
```

---

## Toolchain

- **IDE**: SEGGER Embedded Studio (SES)
- **MCU**: Cortex-M3 (genérico)
- **Lenguajes**: C (principal), Assembly (startup)
- **Build**: desde SES o línea de comandos (si tu toolchain lo permite)

> Abre `project.emProject` en SEGGER para compilar/depurar.

---

## Flujo de arranque (resumen)

1. **Reset/Startup** → inicialización de pila, vector table, clock.
2. **Mem & Peripherals** → configuración mínima (UART/Flash/GPIO).
3. **Self-tests** → CRC/EDAC en regiones críticas.
4. **Boot decision** → selección de imagen primaria / fallback.
5. **Jump** → transferencia a la aplicación/RTOS.

---

## Interfaces mínimas

- **UART**: logs de arranque y resultado de self-tests.
- **Flash**: lectura de headers, verificación de imagen y salto.
- **GPIO** (opcional): señalización de error mediante pin/LED.

---

## Pruebas sugeridas

- **CRC16 / EDAC**: pruebas unitarias sobre buffers conocidos.
- **Mapas de memoria**: verificación de límites y protecciones.
- **Fallback**: forzar fallo de imagen primaria y validar salto a secundaria.
- **Telecommand stub**: comando “PING” → respuesta “PONG/STATUS”.

---

## Alcance y uso

Este repositorio es proyecto de caracter educativo y no corresponde al software de la misión real.

---

## 🏷 Topics

`embedded-c` `bootloader` `cortex-m3` `segger` `rtos` `edac` `crc16` `bsp`
