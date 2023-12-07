#include <iostream>
#include <string>

/**
 * The Graphic interface declares common operations for both Image and the
 * ImageProcy. As long as the client works with Image using this interface,
 * you'll be able to pass it a proxy instead of a real Image.
 */

class Graphic {
  public:
    virtual ~Graphic() = default;
    virtual void Draw() = 0;
};

/**
 * The Image contains some core business logic. Usually, Images are
 * capable of doing some useful work which may also be very slow or sensitive -
 * e.g. correcting input data. A ImageProcy can solve these issues without any
 * changes to the Image's code.
 */
class Image : public Graphic {
  public:
    Image(const std::string fileName) : _fileName(fileName) {
        std::cout << "Image: loading " << _fileName << " image from disk\n";
    }
    void Draw() { std::cout << "Image: drawing " << _fileName << "\n"; }

  private:
    std::string _fileName;
};

class ImageProxy : public Graphic {
  public:
    ImageProxy(const std::string fileName)
        : _image(nullptr), _fileName(fileName) {}
    ~ImageProxy() {
        if (_image != nullptr) {
            delete _image;
        }
    };
    /**
     * The most common applications of the ImageProcy pattern are lazy loading,
     * caching, controlling the access, logging, etc. A ImageProcy can perform
     * one of these things and then, depending on the result, pass the execution
     * to the same method in a linked Image object.
     */
    void Draw() { GetImage()->Draw(); }

  protected:
    Image *GetImage() {
        if (_image == nullptr) {
            std::cout << "ImageProxy: Image not in memory, loading...\n";
            _image = new Image(_fileName);
        }
        return _image;
    }

  private:
    /**
     * The ImageProcy maintains a reference to an object of the Image class. It
     * can be either lazy-loaded or passed to the ImageProcy by the client.
     */
    Image *_image;
    std::string _fileName;
};

/**
 * The client code is supposed to work with all objects (both Image and
 * proxies) via the Graphic interface in order to support both real Image and
 * proxies. In real life, however, clients mostly work with their real Image
 * directly. In this case, to implement the pattern more easily, you can extend
 * your proxy from the real Images's class.
 */
void ClientCode(Graphic &graphic) { graphic.Draw(); }

int main() {
    std::cout << "Client: Executing the client code with a real Image:\n";
    Image *realImage = new Image("Husky.jpg");
    ClientCode(*realImage);
    std::cout << "\n";
    std::cout << "Client: Executing the same client code with a proxy:\n";
    ImageProxy *imageProxy = new ImageProxy("Lena.jpg");
    ClientCode(*imageProxy);

    delete realImage;
    delete imageProxy;
    return 0;
}
