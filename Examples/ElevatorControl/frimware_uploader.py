import threading
import glob
import serial.tools.list_ports
import tkinter as tk
from tkinter import ttk, filedialog
import os
import subprocess
import serial
import requests

class App:
    def __init__(self, root):
        self.root = root
        self.root.title("ESP32 Firmware Uploader")
        
        # Browse button for local .bin file
        self.connection_status = tk.Label(root, text="ESP32 Not Connected", height=1, width=20)
        self.connection_status.pack(pady=10)
        
        # Checkbox to decide downloading .bin or use local
        self.download_var = tk.BooleanVar(value=True)
        self.download_checkbox = ttk.Checkbutton(root, text="Download .bin file from URL", variable=self.download_var)
        self.download_checkbox.pack(pady=10)
        
        # Start button
        self.start_btn = ttk.Button(root, text="Start", command=self.start_process)
        self.start_btn.pack(pady=20)
        
        # Log textbox
        self.log_text = tk.Text(root, height=15, width=60)
        self.log_text.pack(pady=20)
        
        # Scrollbar for log textbox
        self.scrollbar = ttk.Scrollbar(root, command=self.log_text.yview)
        self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.log_text.config(yscrollcommand=self.scrollbar.set)

        # Create Progress bar
        self.progress = ttk.Progressbar(root, orient="horizontal", length=300, mode="determinate")
        self.progress.pack(pady=20)


    def browse_file(self):
        file_path = filedialog.askopenfilename(title="Select .bin file", filetypes=[("BIN files", "*.bin")])
        if file_path:
            self.log(f"Selected {file_path}")

    def log(self, message):
        # Use the 'after' method to schedule the UI update on the main thread
        self.root.after(0, self._log_on_main_thread, message)
        
    def _log_on_main_thread(self, message):
        self.log_text.insert(tk.END, message + "\n")
        self.log_text.see(tk.END)

    def check_arduino_cli(self):
        arduino_cli_path = "C:\\Program Files\\Arduino CLI\\arduino-cli.exe"
        if not os.path.exists(arduino_cli_path):
            self.log("Arduino CLI not found.")
            # Prompt user to download and install
            self.log("Downloading Arduino CLI...")
            # The following line requires the 'requests' library
            response = requests.get("https://downloads.arduino.cc/arduino-cli/arduino-cli_0.34.2_Windows_64bit.msi")
            with open("arduino-cli_installer.msi", "wb") as f:
                f.write(response.content)
            self.log("Please install Arduino CLI using the downloaded installer.")
            # This will execute the installer
            os.system("arduino-cli_installer.msi")
        else:
            self.log("Arduino CLI found.")
        
        # Check if arduino-cli is in the system's PATH
        result = subprocess.run(["where", "arduino-cli"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if "arduino-cli" not in result.stdout:
            self.log("Adding Arduino CLI to system PATH...")
            # This is a simplified way to add it to PATH, might need adjustments
            os.environ["PATH"] += os.pathsep + os.path.dirname(arduino_cli_path)
            
            self.log("Arduino CLI added to system PATH.")
        else:
            self.log("Arduino CLI Exists in system PATH.")

    def detect_connected_ESP32(self):
        ports = serial.tools.list_ports.comports()
        for port in ports:
            if "ESP32" in port.description:  # This might need adjustments based on the actual port description
                self.log(f"ESP32 detected on port {port.device}.")
                return port.device
        self.log("ESP32 not detected.")
        return None

    def download_file(self, file_entry):
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

    def update_progress_bar(self, value):
        self.progress["value"] = value
        root.update_idletasks()

    def get_bin_file_path(self):
        try:
            # If the checkbox is unchecked
            if not self.download_var.get():
                # Search for .ino.bin files in esp32.esp32.esp32 directory
                current_dir = os.getcwd()
                search_path = os.path.join(current_dir, "esp32.esp32.esp32", "*.ino.bin")
                
                files = glob.glob(search_path)
                if files:
                    print(os.getcwd())
                    relative_path = files[0].replace(os.getcwd(), '', 1)

                    return relative_path
                else:
                    self.log("No .ino.bin file found in esp32.esp32.esp32 directory.")
                    return None

            # Fetch the JSON
            response = requests.get("https://portal.aivwa.com/elevator/update.json")
            data = response.json()

            # Calculate progress step
            total_files = len(data["files"])
            progress_step = 100 / total_files

            ino_bin_file_path = ''
            # Download files sequentially
            for file_entry in data["files"]:
                filename = os.path.basename(file_entry["path"])
                if filename.endswith(".ino.bin"):
                    ino_bin_file_path = file_entry["path"]
                result = self.download_file(file_entry)
                self.log(result)
                self.update_progress_bar(self.progress["value"] + progress_step)
            self.log("Download Finished")
            return ino_bin_file_path
        
        except Exception as e:
            self.log(f"Error: {str(e)}")
            self.update_progress_bar(0)
        return None
        
    def detect_connected_ESP32(self):
        ports = serial.tools.list_ports.comports()
        for port in ports:
            # Here, we're assuming that the description or name of the ESP32 contains "ESP32".
            # This assumption might not always be accurate, and you may need to adjust this based on the actual description or name of your ESP32 when connected.
            if "CH340" in port.description:
                self.log(f"ESP32 detected on port {port.device}.")
                self.log("Press Reset and Set Button on Board ...")
                return port.device

        self.log("ESP32 not detected.")
        return None
    
    def check_board_ready_for_download(self, port):
        if not port:
            self.log("No ESP32 detected. Can't check for download readiness.")
            return False

        try:
            with serial.Serial(port, 115200, timeout=1) as ser:
                while True:
                    line = ser.readline().decode("utf-8").strip()
                    if "waiting for download" in line:
                        self.log("Board is ready for download.")
                        break  # This will exit the loop and close the port
        except Exception as e:
            self.log(f"Error while checking board readiness: {e}")
            return False

        return True

    def upload_data(self, port):
        try:
            # Assuming that the upload command might look something like this
            command = f"mklittlefs -c data -b 4096 -p 256 -s 0x310000 spiffs.bin" 
            # Note: [BOARD_NAME] would need to be replaced by the actual board name
            
            result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            
            if result.returncode == 0:
                self.log("spiffs.bin file created successfully.")
                self.log("Uploading spiffs.bin to board ....")
            else:
                self.log(f"Error during upload: {result.stderr}")

            try:
                # Assuming that the upload command might look something like this
                command = f"esptool.exe --chip esp32 --port {port} --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 spiffs.bin" 
                # Note: [BOARD_NAME] would need to be replaced by the actual board name
                result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
                
                if result.returncode == 0:
                    self.log("Data uploaded successfully!")
                else:
                    self.log(f"Error during upload: {result.stderr}")

            except Exception as e:
                self.log(f"Error while creating spiffs.bin: {e}")

            # command = f"arduino-cli upload -p {port} --fqbn esp32:esp32:esp32 --input-file={bin_file_path}" 
        except Exception as e:
            self.log(f"Error while uploading Data: {e}")

    def upload_firmware(self, bin_file_path, port):
        
        try:
            # Assuming that the upload command might look something like this
            command = f"arduino-cli upload -p {port} --fqbn esp32:esp32:esp32 --input-file={bin_file_path}" 
            # Note: [BOARD_NAME] would need to be replaced by the actual board name
            
            result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            
            if result.returncode == 0:
                self.log("Firmware uploaded successfully!")
            else:
                self.log(f"Error during upload: {result.stderr}")

        except Exception as e:
            self.log(f"Error while uploading firmware: {e}")


    def start_process(self):
        self.log("Starting the process...")

        # Start the long-running process on a separate thread
        thread = threading.Thread(target=self.run_task)
        thread.start()
        
    def run_task(self):
        # self.check_arduino_cli() # Uncomment this if needed
        port = self.detect_connected_ESP32()
        if not port:
            self.log("No ESP32 detected. Aborting upload.")
            return

        if not self.check_board_ready_for_download(port):
            self.log("Board is not ready for download. Aborting upload.")
            return
        
        self.upload_firmware(self.get_bin_file_path(), port)
        port = self.detect_connected_ESP32()
        self.check_board_ready_for_download(port)
        # self.upload_data(port)

if __name__ == "__main__":
    root = tk.Tk()
    app = App(root)
    root.mainloop()
