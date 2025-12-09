#
# test_tous_fichiers.py
#


import os
import subprocess
import signal
import pandas as pd


DATA_DIR = "./data"
BIN = "./bin/main"

METHODS = ["nn", "rw", "2optnn", "2optrw", "ga 10 10000 0", "gadpx 10 100 0"]

RESULT_FILE_TSP = "bin/resultats_tsp.txt"
RESULT_FILE_TOUR = "bin/resultats_tour.txt"

NOMBRE_SECONDES_MAX_CALCUL = 60


def main():

    subprocess.run(["make", "clean"])
    subprocess.run(["make", "comparaison_resultat"])

    with open(RESULT_FILE_TOUR, "w") as f:
        f.write("Instance ; Longueur ; Tour\n")

    resultats_tsp = ""

    for filename in sorted(os.listdir(DATA_DIR)):
        if filename.endswith(".opt.tour"):
            resultats_tsp = os.path.join(DATA_DIR, filename)
            resultats_tsp = resultats_tsp[:-8] + "tsp"
            cmd = [BIN, "-f", resultats_tsp, "-m", "bf"]

            p = subprocess.Popen(
                cmd,
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            output, _ = p.communicate()

            if output:
                lines = [l for l in output.splitlines() if l.strip() != ""]
                if lines:
                    last = lines[-1]
                    with open(RESULT_FILE_TOUR, "a") as f:
                        f.write(last + "\n")

    subprocess.run(["make", "clean"])
    subprocess.run(["make", "all"])

    with open(RESULT_FILE_TSP, "w") as f:
        f.write("Instance ; Méthode ; Temps CPU (s) ; Longueur ; Tour\n")

    resultats_tour = ""

    for filename in sorted(os.listdir(DATA_DIR)):
        if filename.endswith(".opt.tour"):
            resultats_tour = os.path.join(DATA_DIR, filename)
            resultats_tour = resultats_tour[:-8] + "tsp"

            for method in METHODS:

                cmd = [BIN, "-f", resultats_tour, "-m"] + method.split()

                p = subprocess.Popen(
                    cmd,
                    stdin=subprocess.PIPE,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE,
                    text=True
                )

                try:
                    p.wait(timeout=NOMBRE_SECONDES_MAX_CALCUL)

                except subprocess.TimeoutExpired:
                    p.send_signal(signal.SIGINT)
                    try:
                        p.stdin.write("n\n")
                        p.stdin.flush()
                    except:
                        pass

                output, _ = p.communicate()

                if output:
                    lines = [l for l in output.splitlines() if l.strip() != ""]
                    if lines:
                        last = lines[-1]
                        with open(RESULT_FILE_TSP, "a") as f:
                            f.write(last + "\n")

    df_tsp = pd.read_csv(RESULT_FILE_TSP, sep=";", engine="python")
    df_tour = pd.read_csv(RESULT_FILE_TOUR, sep=";", engine="python")

    df_tsp = df_tsp.apply(lambda col: col.str.strip()
                          if col.dtype == "object" else col)
    df_tour = df_tour.apply(lambda col: col.str.strip()
                            if col.dtype == "object" else col)

    df_tsp.columns = ["Instance", "Méthode",
                      "Temps CPU (s)", "Longueur", "Tour"]
    df_tour.columns = ["Instance", "Longueur minimale théorique", "Tour"]

    df_tsp = df_tsp.drop(columns=["Tour"])
    df_tour = df_tour.drop(columns=["Tour"])

    df_tsp["Temps CPU (s)"] = pd.to_numeric(
        df_tsp["Temps CPU (s)"], errors="coerce")
    df_tsp["Longueur"] = pd.to_numeric(df_tsp["Longueur"], errors="coerce")
    df_tour["Longueur minimale théorique"] = pd.to_numeric(
        df_tour["Longueur minimale théorique"], errors="coerce")

    df = df_tsp.merge(
        df_tour[["Instance", "Longueur minimale théorique"]], on="Instance", how="left")

    df["Différence (%)"] = ((df["Longueur"] - df["Longueur minimale théorique"]
                             ) / df["Longueur minimale théorique"] * 100).round(2)

    stats = df.groupby("Méthode").agg({
        "Temps CPU (s)": ["mean", "median", lambda x: x.quantile(0.25), lambda x: x.quantile(0.75)],
        "Différence (%)": ["mean", "median", lambda x: x.quantile(0.25), lambda x: x.quantile(0.75)]
    })

    for method, row in stats.iterrows():
        df = pd.concat([df, pd.DataFrame({
            "Instance": [f"Moyenne {method}", f"Q1 {method}", f"Médiane {method}", f"Q3 {method}"],
            "Méthode": [method]*4,
            "Temps CPU (s)": [row[("Temps CPU (s)", "mean")],
                              row[("Temps CPU (s)", "<lambda_0>")],
                              row[("Temps CPU (s)", "median")],
                              row[("Temps CPU (s)", "<lambda_1>")]],
            "Longueur": [None]*4,
            "Longueur minimale théorique": [None]*4,
            "Différence (%)": [row[("Différence (%)", "mean")],
                               row[("Différence (%)", "<lambda_0>")],
                               row[("Différence (%)", "median")],
                               row[("Différence (%)", "<lambda_1>")]]
        })], ignore_index=True)

    df.to_csv("bin/analyse_performance.csv", sep=";", index=False)

    pd.set_option("display.max_rows", None)
    print(df)


if __name__ == "__main__":
    main()
