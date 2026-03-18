# Forecast.ioT

Forecast.ioT is a weather station dashboard that monitors temperature and humidity in real time. Weather data are collected every few seconds, stored, and displayed on a dashboard that updates automatically for easy monitoring.

---

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

![Forecast.ioT Hardware Setup](/arduino/forecast_iot_hardware_setup.jpg)

<p align="center"> Fait avec ❤️ au Sénégal 🇸🇳<br/> <i>Si vous trouvez ce projet utile, n'hésitez pas à lui donner une ⭐️</i> </p> ```
