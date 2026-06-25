from datetime import date
import csv
import os

filename = "study_data.csv"

# Create file with header if it doesn't exist
if not os.path.exists(filename):
    with open(filename, "w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Date", "Sessions"])

# Get today's study sessions
sessions = int(input("How many study sessions today? "))

today = date.today()

# Save data
with open(filename, "a", newline="") as file:
    writer = csv.writer(file)
    writer.writerow([today, sessions])

# Analyze data
total_sessions = 0
days = 0

with open(filename, "r", newline="") as file:
    reader = csv.reader(file)

    next(reader)  # Skip header row

    for row in reader:
        total_sessions += int(row[1])
        days += 1

average = total_sessions / days

print("\n===== STUDY ANALYTICS =====")
print("Total Sessions:", total_sessions)
print("Average Per Day:", round(average, 2))