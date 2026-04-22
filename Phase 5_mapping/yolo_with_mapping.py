import cv2
from ultralytics import YOLO

model = YOLO("yolov8n.pt")

cap = cv2.VideoCapture(1)  # DroidCam

# Define your real-world working area size (in cm)
TABLE_WIDTH_CM = 40
TABLE_HEIGHT_CM = 30

FRAME_WIDTH = 640
FRAME_HEIGHT = 480

target = input("Enter object to detect: ").lower()

while True:
    ret, frame = cap.read()
    if not ret:
        break

    results = model(frame)

    found = False

    for box in results[0].boxes:
        cls_id = int(box.cls[0])
        class_name = model.names[cls_id].lower()
        conf = float(box.conf[0])

        if conf < 0.5:
            continue

        if class_name == target:
            found = True

            x1, y1, x2, y2 = map(int, box.xyxy[0])

            # Center in pixels
            cx = (x1 + x2) // 2
            cy = (y1 + y2) // 2

            # Map to real-world coordinates (cm)
            real_x = (cx / FRAME_WIDTH) * TABLE_WIDTH_CM
            real_y = (cy / FRAME_HEIGHT) * TABLE_HEIGHT_CM

            # Draw
            cv2.rectangle(frame, (x1, y1), (x2, y2), (0,255,0), 2)
            cv2.circle(frame, (cx, cy), 5, (0,0,255), -1)

            text = f"Pixel: ({cx},{cy})  Real: ({real_x:.1f}cm, {real_y:.1f}cm)"
            cv2.putText(frame, text, (20, 30),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255,0,0), 2)

            print(f"Target at: {real_x:.2f} cm , {real_y:.2f} cm")

    if not found:
        cv2.putText(frame, "Target not found", (30, 40),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0,0,255), 2)

    cv2.imshow("YOLO Real World Mapping", frame)

    if cv2.waitKey(1) == 27:
        break

cap.release()
cv2.destroyAllWindows()
