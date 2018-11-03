from keras.preprocessing.image import img_to_array, load_img
from PIL import Image
import csv
import numpy as np

directory = "/home/astar/Desktop/smaller_images/smalldepth_"
img_type = ".jpg"


with open('image_arrays.csv', mode='w') as image_array:
    for i in range(1,25):
        img_path = directory + str(i) + img_type
        img = load_img(img_path)
        x = img_to_array(img)
        new_x = np.array(x)
        new_x=new_x.flatten()
        print (new_x)
        image_writer = csv.writer(image_array, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
        image_writer.writerow(new_x)
