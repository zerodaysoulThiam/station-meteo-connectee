# Forecast.ioT

<p align="center">
  <b>🌡️ Solution IoT complète pour la surveillance météo en temps réel</b><br/>
  <i>De la collecte matérielle à la visualisation interactive des données</i>
</p>

## 📋 Table des matières
- [Aperçu du projet](#-aperçu-du-projet)
- [Architecture technique](#-architecture-technique)
- [Fonctionnalités](#-fonctionnalités)
- [Démonstration](#-démonstration)
- [Stack technologique](#-stack-technologique)
- [Installation](#-installation)
- [Configuration matérielle](#-configuration-matérielle)
- [API Documentation](#-api-documentation)
- [Structure du projet](#-structure-du-projet)
- [Roadmap](#-roadmap)
- [Contributions](#-contributions)
- [Auteur](#-auteur)
- [Licence](#-licence)
---

**Forecast.ioT** est une solution IoT de bout en bout permettant la surveillance météorologique en temps réel. Le système collecte des données de température et d'humidité via des capteurs DHT11 connectés à un Arduino UNO R4 WiFi, les transmet à un backend Node.js, les stocke dans une base de données PostgreSQL (NeonDB), et les visualise sur un dashboard Vue.js interactif.

```mermaid
graph LR
    A[Capteur DHT11] --> B[Arduino UNO R4 WiFi]
    B --> C[API REST Node.js]
    C --> D[(NeonDB PostgreSQL)]
    C --> E[WebSocket]
    E --> F[Dashboard Vue.js]
    F --> G[Chart.js Graphiques]
    F --> H[Indicateurs temps réel]

## Technology Stack

| Category        | Technologies                                                                                                                                                                                                                                                |
| --------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Microcontroller | ![Arduino](https://img.shields.io/badge/Arduino%20UNO%20R4%20WiFi-00979D?style=flat&logo=arduino) ![DHT11](https://img.shields.io/badge/DHT11-sensor-lightgrey)                                                                                             |
| Frontend        | ![Vue.js](https://img.shields.io/badge/Vue%203-35495e?style=flat&logo=vue.js) ![Vite](https://img.shields.io/badge/Vite-646cff?style=flat&logo=vite) ![TypeScript](https://img.shields.io/badge/TypeScript-3178c6?style=flat&logo=typescript)               |
| UI              | ![shadcn-vue](https://img.shields.io/badge/shadcn--vue-ui-ff69b4) ![Tailwind CSS](https://img.shields.io/badge/Tailwind%20CSS-06B6D4?style=flat&logo=tailwindcss) ![lucide-vue-next](https://img.shields.io/badge/lucide--vue--next-icons-7c3aed)           |
| Charts          | ![vue-chartjs](https://img.shields.io/badge/vue--chartjs-3aa6ff) ![Chart.js](https://img.shields.io/badge/Chart.js-ff6384)                                                                                                                                  |
| Backend         | ![Node.js](https://img.shields.io/badge/Node.js-339933?style=flat&logo=node.js) ![Express](https://img.shields.io/badge/Express.js-000000?style=flat&logo=express) ![TypeScript](https://img.shields.io/badge/TypeScript-3178c6?style=flat&logo=typescript) |
| Database        | ![NeonDB](https://img.shields.io/badge/NeonDB-database-blue)                                                                                                                                                                                                |
| ORM             | ![Prisma](https://img.shields.io/badge/Prisma-3b82f6?style=flat&logo=prisma)                                                                                                                                                                                |

---

## Project Structure

```
forecast-iot/
├── arduino/
│   ├── ForecastIoT.ino
│   └── forecast_iot_hardware_setup.jpg
├── backend/
│   ├── prisma/
│   │   └── schema.prisma
│   ├── src/
│   │   ├── lib/prisma.ts
│   │   ├── routes/readings.ts
│   │   └── index.ts
│   └── package.json
└── frontend/
    ├── public/
    └── src/
        ├── App.vue
        ├── main.ts
        ├── views/Dashboard.vue
        └── components/
```

sequenceDiagram
    participant DHT11
    participant Arduino
    participant API
    participant Database
    participant WebSocket
    participant Dashboard
    
    loop Every 30 seconds
        DHT11->>Arduino: Lecture température/humidité
        Arduino->>Arduino: Traitement données
        Arduino->>API: POST /api/sensor-data
        API->>Database: Sauvegarde données
        Database-->>API: Confirmation
        API->>WebSocket: Broadcast nouvelles données
        WebSocket->>Dashboard: Mise à jour temps réel
        Dashboard->>Dashboard: Rafraîchissement graphiques
    end

┌─────────────────────────────────────────────────────────────┐
│  🌤️ Forecast.ioT                                 [🔔] [👤]  │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────────┐  ┌─────────────────┐                   │
│  │    Température   │  │    Humidité     │                   │
│  │     25.5°C      │  │     65%        │                   │
│  │  ↑ +0.5°C/h     │  │  ↓ -2% /h      │                   │
│  └─────────────────┘  └─────────────────┘                   │
│                                                              │
│  ┌─────────────────────────────────────────────────────┐   │
│  │                                                     │   │
│  │           Évolution température 24h                 │   │
│  │                    [Graphique]                      │   │
│  │                                                     │   │
│  └─────────────────────────────────────────────────────┘   │
│                                                              │
│  ┌─────────────┬─────────────┬─────────────┬─────────────┐ │
│  │   Date      │ Température │  Humidité   │   Action    │ │
│  ├─────────────┼─────────────┼─────────────┼─────────────┤ │
│  │ 2024-01-15  │   24.5°C    │    62%      │    📊      │ │
│  │ 2024-01-15  │   24.8°C    │    63%      │    📊      │ │
│  │ 2024-01-15  │   25.1°C    │    64%      │    📊      │ │
│  └─────────────┴─────────────┴─────────────┴─────────────┘ │
└─────────────────────────────────────────────────────────────┘

### Configuration matérielle

graph TD
    subgraph Arduino[Arduino UNO R4 WiFi]
        Pin5[Pin Digital 5]
        Pin5V[5V]
        PinGND[GND]
    end
    
    subgraph DHT11[DHT11 Sensor]
        Data[Data Pin]
        VCC[VCC]
        GND[GND]
    end
    
    Pin5 --> Data
    Pin5V --> VCC
    PinGND --> GND
    
    style Arduino fill:#00979D,color:white
    style DHT11 fill:#4CAF50,color:white

---

## Getting Started

### Prerequisites

- Node.js v18 or higher
- npm v9 or higher
- A NeonDB account
- Arduino IDE 2.x with the Arduino UNO R4 WiFi board package
- Adafruit DHT sensor library and Adafruit Unified Sensor

### Backend

Install dependencies and set up environment:

```bash
cd backend
npm install
# edit .env and add NeonDB connection strings
```

Generate the Prisma client and run migrations:

```bash
npx prisma generate
npx prisma migrate dev --name init
```

Start the backend server:

```bash
npm run dev
```

The API will be available at `http://localhost:3000`.

### Frontend

```bash
cd frontend
npm install
npm run dev
```

The dashboard will be available at `http://localhost:5173`.



---

## Hardware Setup

![Forecast.ioT Hardware Setup](/arduino/forecast_iot_hardware_setup.jpg)<p align="center"> Fait avec ❤️ au Sénégal 🇸🇳<br/> <i>Si vous trouvez ce projet utile, n'hésitez pas à lui donner une ⭐️</i> </p> ```
