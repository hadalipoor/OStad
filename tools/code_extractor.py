import os
import json

def extract_text_from_files(directory, script_path):
    all_text_data = []

    # Recursively walk through all files in the directory and subdirectories
    for root, dirs, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)

            # Skip the current script file
            if os.path.abspath(file_path) == script_path:
                continue

            if file.endswith(".h") or file.endswith(".cpp") or file.endswith(".py") or file.endswith(".json"):
                try:
                    # Read the text file with UTF-8 encoding
                    with open(file_path, 'r', encoding='utf-8') as f:
                        content = f.read()
                    # Append the path and content in JSON format
                    all_text_data.append({"path": file_path, "content": content})
                except UnicodeDecodeError:
                    # Skip the file if there is an encoding issue
                    print(f"Skipping file due to encoding issue: {file_path}")

    return all_text_data

def save_to_file(data, output_file):
    # Write the collected data to the output file
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=4)

def main():
    # Set the directory to scan as the current directory
    directory_to_scan = os.getcwd()

    # Get the absolute path of the current script
    script_path = os.path.abspath(__file__)

    output_file = 'output.txt'

    # Extract text from all .txt files, excluding the current script
    all_text_data = extract_text_from_files(directory_to_scan, script_path)

    # Save the extracted data to a file
    save_to_file(all_text_data, output_file)
    print(f"All data has been saved to {output_file}")

if __name__ == "__main__":
    main()
