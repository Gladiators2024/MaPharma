import cv2
import sys
import os

# Check if a user ID was passed as an argument
if len(sys.argv) > 1:
    user_id = int(sys.argv[1])
else:
    print("No user ID passed.")
    sys.exit(1)

# Define the path to save face images
output_dir = r"C:\Users\SBS\Pictures\wjouh"  # Modify this with your desired path
os.makedirs(output_dir, exist_ok=True)  # Ensure the directory exists

# Initialize the face detection and recognition code as usual
face_cascade = cv2.CascadeClassifier(r"C:\Users\SBS\Downloads\haarcascade_frontalface_default.xml")
cap = cv2.VideoCapture(0)

print(f"Starting face recognition for User {user_id}")
print("Press 'q' to quit or 's' to save a face image.")

while True:
    ret, frame = cap.read()
    if not ret:
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(100, 100))

    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)

        if cv2.waitKey(1) & 0xFF == ord('s'):
            # Save the face image with user ID in the specified directory
            face_path = os.path.join(output_dir, f"face_{user_id}.jpg")
            cv2.imwrite(face_path, gray[y:y+h, x:x+w])
            print(f"Saved face image for User {user_id} at {face_path}.")

    cv2.imshow("Face Recognition", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
