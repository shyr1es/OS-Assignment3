import java.io.*;
import java.net.*;

public class EchoServer {
    public static void main(String[] args) {
        int port = 6017; // Port number for the echo server

        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Echo server is running on port " + port);

            while (true) {
                // Accept a client connection
                Socket clientSocket = serverSocket.accept();
                System.out.println("Client connected.");

                // Handle the client in a separate thread
                new Thread(() -> handleClient(clientSocket)).start();
            }
        } catch (IOException e) {
            System.err.println("Server exception: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (InputStream input = clientSocket.getInputStream();
             OutputStream output = clientSocket.getOutputStream()) {
            
            byte[] buffer = new byte[1024];
            int bytesRead;

            // Read data from the client and echo it back
            while ((bytesRead = input.read(buffer)) != -1) {
                output.write(buffer, 0, bytesRead);
                output.flush();
            }

            System.out.println("Client disconnected.");
        } catch (IOException e) {
            System.err.println("Client handling exception: " + e.getMessage());
        } finally {
            try {
                clientSocket.close();
            } catch (IOException e) {
                System.err.println("Failed to close client socket: " + e.getMessage());
            }
        }
    }
}
