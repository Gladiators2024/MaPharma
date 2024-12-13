import cv2
import sys

# Check if user ID is passed as argument (if needed)
if len(sys.argv) > 1:
    user_id = int(sys.argv[1])
else:
    print("No user ID passed.")
    sys.exit(1)

# Initialize the face detection
face_cascade = cv2.CascadeClassifier(r"C:\Users\SBS\Downloads\haarcascade_frontalface_default.xml")
recognizer = cv2.face.LBPHFaceRecognizer_create()

# Load the trained model (trainer.yml or similar)
recognizer.read(r"C:\Users\SBS\Downloads\trainer.yml")  # Make sure this path is correct

# Start the camera for face recognition
cap = cv2.VideoCapture(0)

print(f"Starting face recognition for User {user_id}")

while True:
    ret, frame = cap.read()
    if not ret:
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(100, 100))

    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
        face = gray[y:y + h, x:x + w]

        # Perform recognition
        id_, confidence = recognizer.predict(face)

        # If confidence is high (indicating a known face)
        if confidence < 100:
            cv2.putText(frame, f"User {id_}", (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)
        else:
            cv2.putText(frame, "Unknown", (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 2)

    cv2.imshow("Face Recognition", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
