// Understanding how asymetric keys can work to send messages and receive encrypted messages.

use chacha20poly1305::{
    ChaCha20Poly1305, KeyInit,
    aead::{Aead, OsRng, rand_core::RngCore},
};
use hkdf::Hkdf;
use sha2::Sha256;
use x25519_dalek::{PublicKey, StaticSecret};

fn random_bytes<const N: usize>() -> [u8; N] {
    let mut buf = [0u8; N];
    OsRng.fill_bytes(&mut buf);
    buf
}

const NONCE_LEN: usize = 12;

fn derive_key(shared_secret: &[u8; 32]) -> [u8; 32] {
    let hk = Hkdf::<Sha256>::new(None, shared_secret);
    let mut okm = [0u8; 32];
    hk.expand(b"chacha20poly1305 key", &mut okm).unwrap();
    okm
}

fn encrypt(data: impl AsRef<[u8]>, key: &[u8; 32]) -> Vec<u8> {
    let cipher = ChaCha20Poly1305::new(key.into());
    let nonce = random_bytes::<NONCE_LEN>();
    let obsf = cipher.encrypt(&nonce.into(), data.as_ref()).unwrap();
    [&nonce[..], &obsf].concat()
}

fn decrypt(data: &[u8], key: &[u8; 32]) -> Vec<u8> {
    let cipher = ChaCha20Poly1305::new(key.into());
    let (nonce, obsf) = data.split_at(NONCE_LEN);
    cipher.decrypt(nonce.into(), obsf).unwrap()
}

/**
* Only the sender and recipient who have shared their public keys and created
* a shared key from them can share messages.
*
* But we have the problem of the man in the middle.
* Alice <-> Malloy (MITM) <-> Bob
* 1. Alice sends her public key to Bob.
* 2. Malloy intercepts it and replaces it with his own public key.
* 3. Bob receives Malloy’s key, thinking it’s Alice’s.
* 4. Bob computes a shared secret with Malloy’s key.
* 5. Malloy does the same with Alice’s key.
*
* Now:
* - Alice and Malloy share one secret.
* - Malloy and Bob share another secret
*
* So Malloy can:
* - Decrypt Alice’s message with the first key,
* - Re-encrypt it with the second key,
* - Send it to Bob,
* - And both ends think they’re talking directly.
*
* Both parties can decrypt and encrypt fine — but they’re actually talking to Malloy!.
*/
fn confidential() {
    let alice_secret = StaticSecret::random_from_rng(&mut OsRng);
    let alice_public = PublicKey::from(&alice_secret);

    let bob_secret = StaticSecret::random_from_rng(&mut OsRng);
    let bob_public = PublicKey::from(&bob_secret);

    let alice_shared_secret = alice_secret.diffie_hellman(&bob_public);
    let bob_shared_secret = bob_secret.diffie_hellman(&alice_public);
    assert_eq!(alice_shared_secret.as_bytes(), bob_shared_secret.as_bytes());

    let alice_key = derive_key(alice_shared_secret.as_bytes());
    let bob_key = derive_key(bob_shared_secret.as_bytes());
    assert_eq!(alice_key, bob_key);

    let msg = "hello bob";
    let enc = encrypt(msg, &alice_key);
    let dec = decrypt(&enc, &bob_key);

    assert_eq!(msg.as_bytes(), dec);
}

fn main() {
    confidential();
}
