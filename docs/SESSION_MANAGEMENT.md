# Session Management

États : IDLE, HANDSHAKE_PENDING, ESTABLISHED, CLOSING, CLOSED.

Une seule session active par paire en v1. Nonces cryptographiques frais des deux côtés. Transcript lie version, IDs, rôles, nonces et capacités. HKDF utilise un salt lié au transcript et des labels distincts pour clés directionnelles et préfixes. Pas de DATA avant confirmation mutuelle. Reset, échec d'authentification ou épuisement séquence détruit la session. Les formats binaires exacts HELLO/HELLO_ACK/FINISH/SESSION_READY doivent être figés par vecteurs de test.
