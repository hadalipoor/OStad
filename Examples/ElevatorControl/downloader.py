import glob
import tkinter as tk
from tkinter import ttk, scrolledtext
import requests
import os

# GUI Functions
def update_progress_bar(value):
    progress["value"] = value
    root.update_idletasks()

def log_message(message):
    log_text.insert(tk.END, message + "\n")
    log_text.see(tk.END)

def on_start():
    try:
        # Fetch the JSON
        response = requests.get("https://portal.aivwa.com/elevator/update.json")
        data = response.json()

        # Calculate progress step
        total_files = len(data["files"])
        progress_step = 100 / total_files

        # Download files sequentially
        for file_entry in data["files"]:
            result = download_file(file_entry)
            log_message(result)
            update_progress_bar(progress["value"] + progress_step)
        log_message("Download Finished")
    except Exception as e:
        log_message(f"Error: {str(e)}")
        update_progress_bar(0)

def download_file(file_entry):
    try:
        # Create directory if it doesn't exist
        current_dir = os.getcwd()
        
        # Extract directory path and filename from the file_entry["path"]
        dir_only = os.path.dirname(file_entry["path"])
        filename = os.path.basename(file_entry["path"])
        
        dir_path = os.path.join(current_dir, dir_only.strip("\\"))
        if not os.path.exists(dir_path):
            os.makedirs(dir_path)

        # Construct the full path for the file to be saved
        full_file_path = os.path.join(dir_path, filename)

        # Download the file
        response = requests.get(file_entry["url"], stream=True)
        with open(full_file_path, 'wb') as f:
            for chunk in response.iter_content(chunk_size=8192):
                f.write(chunk)
        
        return f"Downloaded {file_entry['url']} to {full_file_path}"
    except Exception as e:
        return f"Error downloading {file_entry['url']}: {str(e)}"

# Initialize the main window
root = tk.Tk()
root.title("File Downloader")
root.geometry("500x400")

# Create Start button
start_button = ttk.Button(root, text="Start Download", command=on_start)
start_button.pack(pady=20)

# Create Progress bar
progress = ttk.Progressbar(root, orient="horizontal", length=300, mode="determinate")
progress.pack(pady=20)

# Create a log textbox
log_text = scrolledtext.ScrolledText(root, wrap=tk.WORD, width=50, height=10)
log_text.pack(pady=20)

root.mainloop()
