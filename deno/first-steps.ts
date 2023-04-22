console.log('Welcome to Deno!')

// --- MAKING AN HTTP REQUEST ---
// $ deno run first-steps.ts https://yirenlu.com/

const url = Deno.args[0]
const res = await fetch(url)

const body = new Uint8Array(await res.arrayBuffer())
await Deno.stdout.write(body)

// --- READING A FILE ---
import { copy } from 'https://deno.land/std@0.167.0/streams/conversion.ts'
const filenames = Deno.args
for (const filename of filenames) {
  const file = await Deno.open(filename)
  await copy(file, Deno.stdout)
  file.close()
}
