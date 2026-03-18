import type { Reading } from "@/types/reading";

// The backend must be running locally during development
const API_BASE = "http://localhost:3000/api";

/**
 * Fetches the latest N readings from the backend, ordered newest first.
 * @param limit - Number of readings to retrieve (default: 50)
 */
export async function fetchReadings(limit = 50): Promise<Reading[]> {
  const res = await fetch(`${API_BASE}/readings?limit=${limit}`);
  if (!res.ok) {
    throw new Error(`Failed to fetch readings: ${res.statusText}`);
  }
  return res.json() as Promise<Reading[]>;
}
