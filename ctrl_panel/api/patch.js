export default async function handler(req, res) {
    const password = process.env.PASSWORD
    if (!password || req.headers["x-password"] != password)
        return res.status(401).end();

    const values = req.body?.values

    const key = process.env.SUPABASE_KEY
    const url = process.env.SUPABASE_URL + "/rest/v1/elevator_status?id=eq.1"

    const response = await fetch(url, {
        method: values ? "PATCH" : "GET",
        headers: {
            apikey: key,
            Authorization: "Bearer " + key,
            "Content-Type": "application/json",
            Prefer: "return=representation",
        },
        body: values ? JSON.stringify(values) : undefined,
    })

    res.status(response.status).send(await response.text())
}
