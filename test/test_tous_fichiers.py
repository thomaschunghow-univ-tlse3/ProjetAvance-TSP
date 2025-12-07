#
# test_tous_fichiers.py
#

import os
import subprocess
import signal

DATA_DIR = "./data/tsp"
BIN = "./bin/main"

METHODS = ["nn", "rw", "2optnn", "2optrw", "ga 10 1000000 .1", "gadpx 10 1000000 .1", "nn"]

RESULT_FILE = "resultats.txt"


def main():

    with open(RESULT_FILE, "w") as f:
        f.write("Instance ; Méthode ; Temps CPU (s) ; Longueur ; Tour ;\n")

    for filename in os.listdir(DATA_DIR):
        if filename.endswith(".tsp"):
            filepath = os.path.join(DATA_DIR, filename)

            for method in METHODS:

                cmd = [BIN, "-f", filepath, "-m"] + method.split()

                p = subprocess.Popen(
                    cmd,
                    stdin=subprocess.PIPE,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE,
                    text=True
                )

                try:
                    p.wait(timeout=10)

                except subprocess.TimeoutExpired:
                    # envoyer Ctrl-C
                    p.send_signal(signal.SIGINT)

                    # envoyer "n" à ton programme
                    try:
                        p.stdin.write("n\n")
                        p.stdin.flush()
                    except:
                        pass

                # récupérer tout ce qui a été écrit
                output, _ = p.communicate()

                # sortie éventuelle
                if output:
                    # Récupérer la dernière ligne non vide
                    lines = [l for l in output.splitlines() if l.strip() != ""]
                    if lines:
                        last = lines[-1]  # la dernière ligne
                        with open(RESULT_FILE, "a") as f:
                            f.write(last + "\n")


if __name__ == "__main__":
    main()
