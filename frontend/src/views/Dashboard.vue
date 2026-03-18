<template>
  <div class="min-h-screen bg-background px-6 py-8">
    <!-- Header -->
    <header class="mb-8 flex items-center justify-between">
      <div class="flex items-center gap-3">
        <img
          src="/forecast_iot_logo.png"
          class="h-10 w-10"
          alt="Forecast.ioT icon"
        />
        <div>
          <h1 class="text-xl font-black tracking-tight text-foreground">
            Forecast.ioT
          </h1>
          <p class="text-xs font-light text-muted-foreground">
            Live weather station dashboard developed by Mariel A. Gravidez of
            MI231
          </p>
        </div>
      </div>
      <div
        class="flex items-center gap-2 text-xs font-light text-muted-foreground"
      >
        <RefreshCw
          :class="[
            'h-3.5 w-3.5',
            isRefreshing ? 'animate-spin text-primary' : '',
          ]"
        />
        <span>Auto-refresh every 5s</span>
        <span v-if="lastUpdated" class="ml-2 text-foreground/50">
          &bull; Last updated {{ lastUpdated }}
        </span>
      </div>
    </header>

    <!-- Error Banner -->
    <div
      v-if="error"
      class="mb-6 flex items-center gap-3 rounded-lg border border-red-900 bg-red-950/60 px-4 py-3 text-sm font-light text-red-300"
    >
      <AlertCircle class="h-4 w-4 flex-shrink-0" />
      <span>{{ error }}</span>
    </div>

    <!-- Tabs -->
    <Tabs default-value="overview">
      <TabsList>
        <TabsTrigger value="overview">Overview</TabsTrigger>
        <TabsTrigger value="history">History</TabsTrigger>
      </TabsList>

      <!-- Tab 1: Stat Cards + Charts -->
      <TabsContent value="overview">
        <!-- Stat Cards -->
        <section class="mb-8 grid grid-cols-1 gap-4 sm:grid-cols-2">
          <!-- Temperature Card -->
          <Card class="shadow-sm border-0" style="background: #4f63d2">
            <CardHeader class="pb-2">
              <div class="flex items-center justify-between">
                <CardTitle class="text-3xl font-black text-white/90"
                  >Temperature</CardTitle
                >
                <div
                  class="flex h-14 w-14 items-center justify-center rounded-full bg-white/20"
                >
                  <Thermometer class="h-10 w-10 text-white" />
                </div>
              </div>
            </CardHeader>
            <CardContent>
              <div v-if="latest" class="flex items-end gap-2">
                <span class="text-4xl font-black text-white">{{
                  latest.temperature.toFixed(1)
                }}</span>
                <span class="mb-1 text-xl font-light text-white/70"
                  >&deg;C</span
                >
              </div>
              <div v-else class="text-3xl font-black text-white/50">--</div>
              <p class="mt-1 text-xs font-light text-white/60">
                Current reading from DHT11 sensor
              </p>
            </CardContent>
          </Card>

          <!-- Humidity Card -->
          <Card class="shadow-sm border-0" style="background: #7c3aed">
            <CardHeader class="pb-2">
              <div class="flex items-center justify-between">
                <CardTitle class="text-3xl font-black text-white/90"
                  >Humidity</CardTitle
                >
                <div
                  class="flex h-14 w-14 items-center justify-center rounded-full bg-white/20"
                >
                  <Droplets class="h-10 w-10 text-white" />
                </div>
              </div>
            </CardHeader>
            <CardContent>
              <div v-if="latest" class="flex items-end gap-2">
                <span class="text-4xl font-black text-white">{{
                  latest.humidity.toFixed(1)
                }}</span>
                <span class="mb-1 text-xl font-light text-white/70">%</span>
              </div>
              <div v-else class="text-2xl font-black text-white/50">--</div>
              <p class="mt-1 text-xs font-light text-white/60">
                Current reading from DHT11 sensor
              </p>
            </CardContent>
          </Card>
        </section>

        <!-- Charts -->
        <section class="grid grid-cols-1 gap-4 lg:grid-cols-2">
          <!-- Temperature Chart -->
          <Card>
            <CardHeader>
              <div class="flex items-center gap-2">
                <Thermometer class="h-4 w-4 text-primary" />
                <CardTitle class="text-sm font-black"
                  >Temperature Over Time</CardTitle
                >
              </div>
              <p class="text-xs font-light text-muted-foreground">
                Last 10 readings (&deg;C)
              </p>
            </CardHeader>
            <CardContent>
              <div v-if="chartReadings.length > 0" class="h-52">
                <Line :data="temperatureChartData" :options="chartOptions" />
              </div>
              <div
                v-else
                class="flex h-52 items-center justify-center text-sm font-light text-muted-foreground"
              >
                Waiting for data...
              </div>
            </CardContent>
          </Card>

          <!-- Humidity Chart -->
          <Card>
            <CardHeader>
              <div class="flex items-center gap-2">
                <Droplets class="h-4 w-4 text-violet-500" />
                <CardTitle class="text-sm font-black"
                  >Humidity Over Time</CardTitle
                >
              </div>
              <p class="text-xs font-light text-muted-foreground">
                Last 10 readings (%)
              </p>
            </CardHeader>
            <CardContent>
              <div v-if="chartReadings.length > 0" class="h-52">
                <Line :data="humidityChartData" :options="chartOptions" />
              </div>
              <div
                v-else
                class="flex h-52 items-center justify-center text-sm font-light text-muted-foreground"
              >
                Waiting for data...
              </div>
            </CardContent>
          </Card>
        </section>
      </TabsContent>

      <!-- Tab 2: Data Table -->
      <TabsContent value="history">
        <section>
          <Card>
            <CardHeader>
              <div class="flex items-center gap-2">
                <TableIcon class="h-4 w-4 text-muted-foreground" />
                <CardTitle class="text-sm font-black"
                  >Recent Readings</CardTitle
                >
              </div>
              <p class="text-xs font-light text-muted-foreground">
                Latest 20 entries from the database
              </p>
            </CardHeader>
            <CardContent class="p-0">
              <Table>
                <TableHeader>
                  <TableRow class="bg-muted/40 hover:bg-muted/40">
                    <TableHead class="w-12 pl-6 font-black">#</TableHead>
                    <TableHead class="font-black">
                      <div class="flex items-center gap-1.5">
                        <Thermometer class="h-3.5 w-3.5 text-primary" />
                        Temperature (&deg;C)
                      </div>
                    </TableHead>
                    <TableHead class="font-black">
                      <div class="flex items-center gap-1.5">
                        <Droplets class="h-3.5 w-3.5 text-violet-500" />
                        Humidity (%)
                      </div>
                    </TableHead>
                    <TableHead class="font-black">
                      <div class="flex items-center gap-1.5">
                        <Clock class="h-3.5 w-3.5 text-muted-foreground" />
                        Timestamp
                      </div>
                    </TableHead>
                  </TableRow>
                </TableHeader>
                <TableBody>
                  <TableRow v-if="tableReadings.length === 0">
                    <TableCell
                      colspan="4"
                      class="py-10 text-center text-sm font-light text-muted-foreground pl-6"
                    >
                      No readings yet. Waiting for data from the sensor...
                    </TableCell>
                  </TableRow>
                  <TableRow
                    v-for="(reading, index) in tableReadings"
                    :key="reading.id"
                    :class="index % 2 === 0 ? 'bg-card' : 'bg-muted/20'"
                  >
                    <TableCell
                      class="pl-6 font-mono text-xs font-light text-muted-foreground"
                      >{{ reading.id }}</TableCell
                    >
                    <TableCell>
                      <span class="font-light text-white">{{
                        reading.temperature.toFixed(1)
                      }}</span>
                      <span class="ml-1 text-xs font-light text-white/60"
                        >&deg;C</span
                      >
                    </TableCell>
                    <TableCell>
                      <span class="font-light text-white">{{
                        reading.humidity.toFixed(1)
                      }}</span>
                      <span class="ml-1 text-xs font-light text-white/60"
                        >%</span
                      >
                    </TableCell>
                    <TableCell class="text-sm font-light text-muted-foreground">
                      {{ formatTimestamp(reading.createdAt) }}
                    </TableCell>
                  </TableRow>
                </TableBody>
              </Table>
            </CardContent>
          </Card>
        </section>
      </TabsContent>
    </Tabs>
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted, onUnmounted } from "vue"
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
  Filler,
  type ChartOptions,
} from "chart.js"
import { Line } from "vue-chartjs"
import {
  Thermometer,
  Droplets,
  RefreshCw,
  AlertCircle,
  Clock,
  Table as TableIcon,
} from "lucide-vue-next"

import { Card, CardHeader, CardTitle, CardContent } from "@/components/ui/card"
import {
  Table,
  TableHeader,
  TableBody,
  TableRow,
  TableHead,
  TableCell,
} from "@/components/ui/table"
import { Tabs, TabsList, TabsTrigger, TabsContent } from "@/components/ui/tabs"
import { fetchReadings } from "@/services/api"
import type { Reading } from "@/types/reading"

// Register Chart.js modules
ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
  Filler
)

const readings = ref<Reading[]>([])
const error = ref<string | null>(null)
const isRefreshing = ref(false)
const lastUpdated = ref<string | null>(null)

let refreshInterval: ReturnType<typeof setInterval> | null = null

// Most recent reading for the stat cards
const latest = computed<Reading | null>(() =>
  readings.value.length > 0 ? readings.value[0] : null
)

// Last 10 readings reversed to chronological order for charts
const chartReadings = computed<Reading[]>(() =>
  [...readings.value].slice(0, 10).reverse()
)

// Last 20 readings sorted descending by ID for the table
const tableReadings = computed<Reading[]>(() =>
  [...readings.value].sort((a, b) => b.id - a.id)
)

// Labels derived from the createdAt timestamps for chart x-axis
const chartLabels = computed<string[]>(() =>
  chartReadings.value.map((r) => formatChartLabel(r.createdAt))
)

const temperatureChartData = computed(() => ({
  labels: chartLabels.value,
  datasets: [
    {
      label: "Temperature (°C)",
      data: chartReadings.value.map((r) => r.temperature),
      borderColor: "#6367FF",
      backgroundColor: "rgba(99, 103, 255, 0.08)",
      borderWidth: 2,
      pointRadius: 2,
      pointHoverRadius: 5,
      tension: 0.3,
      fill: true,
    },
  ],
}))

const humidityChartData = computed(() => ({
  labels: chartLabels.value,
  datasets: [
    {
      label: "Humidity (%)",
      data: chartReadings.value.map((r) => r.humidity),
      borderColor: "#a78bfa",
      backgroundColor: "rgba(167, 139, 250, 0.08)",
      borderWidth: 2,
      pointRadius: 2,
      pointHoverRadius: 5,
      tension: 0.3,
      fill: true,
    },
  ],
}))

// Shared options for both charts
const chartOptions: ChartOptions<"line"> = {
  responsive: true,
  maintainAspectRatio: false,
  plugins: {
    legend: { display: false },
    tooltip: {
      backgroundColor: "#1e1b4b",
      titleColor: "#C9BEFF",
      bodyColor: "#ffffff",
      padding: 10,
      cornerRadius: 8,
      displayColors: false,
    },
  },
  scales: {
    x: {
      grid: { display: false },
      ticks: {
        color: "#94a3b8",
        font: { size: 10 },
        maxTicksLimit: 8,
        maxRotation: 0,
      },
    },
    y: {
      grid: { color: "rgba(0,0,0,0.05)" },
      ticks: { color: "#94a3b8", font: { size: 10 } },
      beginAtZero: false,
    },
  },
}

// Format a timestamp for chart labels (HH:MM:SS)
function formatChartLabel(isoString: string): string {
  const d = new Date(isoString)
  return d.toLocaleTimeString("en-PH", {
    hour: "2-digit",
    minute: "2-digit",
    second: "2-digit",
    hour12: false,
  })
}

// Format a timestamp for the data table (full readable date + time)
function formatTimestamp(isoString: string): string {
  const d = new Date(isoString)
  return d.toLocaleString("en-PH", {
    year: "numeric",
    month: "short",
    day: "2-digit",
    hour: "2-digit",
    minute: "2-digit",
    second: "2-digit",
    hour12: false,
  })
}

async function loadReadings(): Promise<void> {
  isRefreshing.value = true
  try {
    readings.value = await fetchReadings(50)
    error.value = null
    lastUpdated.value = new Date().toLocaleTimeString("en-PH", {
      hour12: false,
    })
  } catch (err) {
    error.value =
      "Could not reach the backend API. Make sure the backend server is running on http://localhost:3000."
    console.error(err)
  } finally {
    isRefreshing.value = false
  }
}

onMounted(() => {
  loadReadings()
  // Poll every 5 seconds to match the Arduino send interval
  refreshInterval = setInterval(loadReadings, 5000)
})

onUnmounted(() => {
  if (refreshInterval !== null) {
    clearInterval(refreshInterval)
  }
})
</script>
