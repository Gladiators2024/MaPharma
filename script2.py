import cv2
import os
import numpy as np

# Path to the folder containing face images
face_data_path = r"C:\Users\SBS\Pictures\wjouh"
output_model_path = r"C:\Users\SBS\Downloads\trainer.yml"

# Initialize Haar Cascade for face detection
face_cascade = cv2.CascadeClassifier(r"C:\Users\SBS\Downloads\haarcascade_frontalface_default.xml")

# Prepare data for training
face_samples = []
ids = []
names = {}

# Loop through the images in the face_data folder
image_paths = [os.path.join(face_data_path, f) for f in os.listdir(face_data_path) if f.endswith(".jpg")]

for image_path in image_paths:
    # Load the image
    img = cv2.imread(image_path)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Detect faces in the image
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(100, 100))

    for (x, y, w, h) in faces:
        face = gray[y:y+h, x:x+w]
        face_samples.append(face)

        # Extract ID from filename (e.g., user_1_face_1.jpg -> ID = 1)
        id = int(image_path.split('_')[1])  # Assuming filenames like "user_1_face_1.jpg"
        ids.append(id)

        # Store names for later use
        if id not in names:
            names[id] = f"User {id}"

# Train the face recognizer using the collected data
recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.train(face_samples, np.array(ids))

# Save the trained model to a file
recognizer.save(output_model_path)

print("Training complete. Model saved as trainer.yml")
