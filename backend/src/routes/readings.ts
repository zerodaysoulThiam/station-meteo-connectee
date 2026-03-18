import { Router, Request, Response } from "express"
import { prisma } from "../lib/prisma"

const router = Router()

// POST /api/readings
// Receives a new temperature + humidity reading from the Arduino and stores it.
router.post("/", async (req: Request, res: Response) => {
  const { temperature, humidity } = req.body

  if (temperature === undefined || humidity === undefined) {
    res.status(400).json({
      error: "Both temperature and humidity fields are required.",
    })
    return
  }

  const temp = parseFloat(temperature)
  const hum = parseFloat(humidity)

  if (isNaN(temp) || isNaN(hum)) {
    res.status(400).json({
      error: "temperature and humidity must be valid numbers.",
    })
    return
  }

  try {
    const reading = await prisma.forecastIOT.create({
      data: {
        temperature: temp,
        humidity: hum,
      },
      select: {
        id: true,
        temperature: true,
        humidity: true,
        createdAt: true,
      },
    })

    res.status(201).json(reading)
  } catch (error) {
    console.error("Failed to create reading:", error)
    res.status(500).json({ error: "Internal server error." })
  }
})

// GET /api/readings
// Retrieves stored readings ordered by latest first.
// Optional query parameter: ?limit=N (defaults to 50)
router.get("/", async (req: Request, res: Response) => {
  const limitParam = req.query.limit
  const limit = limitParam ? parseInt(limitParam as string, 10) : 50

  if (isNaN(limit) || limit < 1) {
    res.status(400).json({ error: "limit must be a positive integer." })
    return
  }

  try {
    const readings = await prisma.forecastIOT.findMany({
      orderBy: { createdAt: "desc" },
      take: limit,
      select: {
        id: true,
        temperature: true,
        humidity: true,
        createdAt: true,
      },
    })

    res.status(200).json(readings)
  } catch (error) {
    console.error("Failed to fetch readings:", error)
    res.status(500).json({ error: "Internal server error." })
  }
})

export default router
