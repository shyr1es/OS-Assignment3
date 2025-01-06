import java.io.*;
import java.net.*;

public class EchoClient {
    public static void main(String[] args) {
        String hostname = "localhost";
        int port = 6017;

        try (Socket socket = new Socket(hostname, port);
             BufferedReader userInput = new BufferedReader(new InputStreamReader(System.in));
             OutputStream output = socket.getOutputStream();
             InputStream input = socket.getInputStream()) {

            System.out.println("Connected to the echo server. Type your messages below:");

            byte[] buffer = new byte[1024];
            int bytesRead;

            // Continuously read user input and send to the server
            while (true) {
                System.out.print("Enter message: ");
                String message = userInput.readLine();
                if (message.equalsIgnoreCase("exit")) {
                    System.out.println("Closing connection.");
                    break;
                }

                // Send message to the server
                output.write(message.getBytes());
                output.flush();

                // Receive and print the echoed message
                bytesRead = input.read(buffer);
                System.out.println("Server echoed: " + new String(buffer, 0, bytesRead));
            }
        } catch (IOException e) {
            System.err.println("Client exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
