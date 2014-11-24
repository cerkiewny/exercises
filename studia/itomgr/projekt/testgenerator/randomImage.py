
import urllib

import string
import random
def id_generator(size=6, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

for i in range(0,10):
    image_name = id_generator()
    urllib.urlretrieve("http://chart.apis.google.com/chart?chst=d_text_outline&chld=ffffff|120|h|ffffff|_|" + image_name , "../SAMPLE_IMAGES/bare_" + str(image_name) + ".jpg")
